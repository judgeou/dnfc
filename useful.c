#include <Windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <string.h>
#include <stdio.h>
#include "baseAddress.h"

void printErrCode () {
  printf("ErrorCode: %d\n", (int)GetLastError());
}

struct ProcessInfo {
  HANDLE pHandle;
  DWORD pId;
};

struct HookPoint {
  ADDRESS address;
  unsigned char * originalBytes;
  int originalBytesSize;
  ADDRESS allocAddr;
  int allocSize;
};

void copyArray (char * target, char * source, int length) {
  for (int i = 0; i < length; i++) {
    target[i] = source[i];
  }
}

BOOL readPointerBuffer (
  ADDRESS address,
  int * offsets,
  int offsetsLen,
  int readSize,
  char * buffer,
  HANDLE pHandle
) {
  if (offsetsLen == 0) {
    return ReadProcessMemory(pHandle, (LPCVOID)address, buffer, readSize, NULL);
  } else {
    char ptr[4];
    ReadProcessMemory(pHandle, (LPCVOID)address, ptr, sizeof(ptr), NULL);
    for (int i = 0; i < offsetsLen; i++) {
      ADDRESS ptrAddr = (ADDRESS)(*(int*)ptr + offsets[i]);
      if (i == offsetsLen - 1) {
        ReadProcessMemory(pHandle, (LPCVOID)ptrAddr, buffer, readSize, NULL);
      } else {
        ReadProcessMemory(pHandle, (LPCVOID)ptrAddr, ptr, sizeof(ptr), NULL);
      }
    }
    return TRUE;
  }
}

/**
 * 无视保护强奸写入后还原保护
 */
BOOL WriteProcessMemoryForce(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten) {
  DWORD oldMeminfo, newMeminfo;
  newMeminfo = PAGE_EXECUTE_READWRITE;
  if (VirtualProtectEx(hProcess, lpBaseAddress, nSize, newMeminfo, &oldMeminfo)) {
    WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
    DWORD old;
    return VirtualProtectEx(hProcess, lpBaseAddress, nSize, oldMeminfo, &old);
  } else {
    return FALSE;
  }
}

BOOL writePointerBuffer (
  ADDRESS address,
  int * offsets,
  int offsetsLen,
  int writeSize,
  char * buffer,
  HANDLE pHandle
) {
  if (offsetsLen == 0) {
    return WriteProcessMemoryForce(pHandle, (LPVOID)address, buffer, writeSize, NULL);
  } else {
    char ptr[4];
    ReadProcessMemory(pHandle, (LPCVOID)address, ptr, sizeof(ptr), NULL);
    for (int i = 0; i < offsetsLen; i++) {
      ADDRESS ptrAddr = (ADDRESS)(*(int*)ptr + offsets[i]);
      if (i == offsetsLen - 1) {
        return WriteProcessMemoryForce(pHandle, (LPVOID)ptrAddr, buffer, writeSize, NULL);
      } else {
        ReadProcessMemory(pHandle, (LPCVOID)ptrAddr, ptr, sizeof(ptr), NULL);
      }
    }
    return TRUE;
  }
}

ADDRESS hook (HANDLE pHandle, struct HookPoint *hookpoint, unsigned char * code, int codeSize) {
  // 加上覆盖代码的字节和跳转字节
  int rCodeSize = codeSize + hookpoint->originalBytesSize + 5;
  unsigned char * rCode = malloc(rCodeSize);
  memcpy(rCode, code, codeSize);
  ADDRESS jmpAddr;
  if (!hookpoint->allocAddr) {
    jmpAddr = (ADDRESS)VirtualAllocEx(pHandle, NULL, rCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    hookpoint->allocAddr = jmpAddr;
    hookpoint->allocSize = rCodeSize;
  } else {
    DWORD old;
    VirtualProtectEx(pHandle, (LPVOID)hookpoint->allocAddr, hookpoint->allocSize, PAGE_EXECUTE_READWRITE, &old);
    jmpAddr = hookpoint->allocAddr;
  }
  if (!jmpAddr) {
    printErrCode();
  }

  // 插入被覆盖的原代码
  memcpy(&rCode[codeSize], hookpoint->originalBytes, hookpoint->originalBytesSize);

  // 插入跳回代码
  rCode[codeSize + hookpoint->originalBytesSize] = 0xE9;
  *(int*)&rCode[codeSize + hookpoint->originalBytesSize + 1] = (hookpoint->address + hookpoint->originalBytesSize) - (jmpAddr + rCodeSize);

  if (WriteProcessMemory(pHandle, (LPVOID)jmpAddr, rCode, rCodeSize, NULL)) {
    // 写入跳转
    unsigned char jmpBytes[5];
    jmpBytes[0] = 0xE9;
    *(int*)&jmpBytes[1] = jmpAddr - hookpoint->address - 5;
    BOOL r = WriteProcessMemoryForce(pHandle, (LPVOID)hookpoint->address, jmpBytes, 5, NULL);
    return r? jmpAddr: 0;
  } else {
    return FALSE;
  }
}

BOOL hookRecovery (HANDLE pHandle, struct HookPoint *hookpoint) {
  if (WriteProcessMemoryForce(
    pHandle,
    (LPVOID)hookpoint->address,
    hookpoint->originalBytes,
    hookpoint->originalBytesSize,
    NULL
  )) {
    DWORD old;
    Sleep(100);
    BOOL r = VirtualProtectEx(pHandle, (LPVOID)hookpoint->allocAddr, hookpoint->allocSize, PAGE_NOACCESS, &old);
    if (!r) {
      printErrCode();
    }
    return r;
  } else {
    return FALSE;
  }
}

/**
 * 获取进程信息
 * @param name 进程名
 */
struct ProcessInfo getProcessByName(const char * name) {
  struct ProcessInfo nullResult;
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);

  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, (DWORD)NULL);

  if (Process32First(snapshot, &entry) == TRUE) {
    while (Process32Next(snapshot, &entry) == TRUE) {
      if (strcmp(entry.szExeFile, name) == 0) {
        struct ProcessInfo info;
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
        info.pHandle = hProcess;
        info.pId = entry.th32ProcessID;
        return info;
      }
    }
    return nullResult;
  } else {
    return nullResult;
  }
}

/**
 * 获取进程模块地址
 */
ADDRESS getModuleBaseAddr (char * name, DWORD pid) {
  MODULEENTRY32 entry;
  entry.dwSize = sizeof(MODULEENTRY32);
  HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, pid);

  if (Module32First(SnapShot, &entry) == TRUE) {
    while(Module32Next(SnapShot, &entry)) {
      if (strcmp(entry.szModule, name)) {
        CloseHandle(SnapShot);
        return (ADDRESS)entry.modBaseAddr;
      }
    }
    CloseHandle(SnapShot);
    return 0x0;
  } else {
    printErrCode();
    CloseHandle(SnapShot);
    return 0x0;
  }
}

void toHex (unsigned char * arr, char * resultStr, int size) {
  for (int i = 0; i < size; i++) {
    char s[4];
    sprintf(s, "%.2x ", arr[i]);
    resultStr[i * 3 + 0] = s[0];
    resultStr[i * 3 + 1] = s[1];
    resultStr[i * 3 + 2] = s[2];
  }
  resultStr[(size - 1) * 3 + 3] = '\0';
}
