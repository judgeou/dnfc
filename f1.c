#pragma comment(lib, "user32")
#include <stdio.h>
#include <Windows.h>
#include "useful.c"
#include "pureuse.c"

int main () {
  unsigned char * byteArr = (unsigned char *)malloc(1024);
  int byteSize = readBytesBetweenTwoFunc(beginFunc, endFunc, byteArr);
  struct ProcessInfo info = getProcessByName("DNF.exe");

  ADDRESS mycode = (ADDRESS)VirtualAllocEx(info.pHandle, NULL, byteSize, MEM_COMMIT, PAGE_EXECUTE);
  if (!mycode) {
    printErrCode();
  }
  BOOL r1 = WriteProcessMemoryForce(info.pHandle, (LPVOID)mycode, byteArr, byteSize, NULL);

  int killthemallAddr = mycode + ((int)killthemall - (int)beginFunc);

  if (mycode && r1) {
    printf("write %d bytes %x\n", byteSize, mycode);
  } else {
    printErrCode();
    return 0;
  }

  unsigned char originalBytes[] = { 0x8B, 0x90, 0x14, 0x06, 00, 00 };
  struct HookPoint loopPoint = { 
    .address = HOOK_LOOP,
    .originalBytes = originalBytes,
    .originalBytesSize = 6,
    .allocAddr = 0,
    .allocSize = 0
  };

  unsigned char code[] = { 0x60, 0xB8, 0x00, 00, 00, 00, 0xFF, 0xD0, 0x61 };
  *(int*)&code[2] = killthemallAddr;

  while (info.pHandle) {
    SHORT s = GetAsyncKeyState(VK_F1);
    if (s) {
      ADDRESS codeAddr = hook(info.pHandle, &loopPoint, code, sizeof(code));
      printf("kill %x\n", codeAddr);
      Sleep(50);
      hookRecovery(info.pHandle, &loopPoint);
    }

    SHORT f2 = GetAsyncKeyState(VK_F2);
    if (f2) {
      int offsets[] = { 0xc0c };
      int value = 741741;
      writePointerBuffer(SSS_ADDR, offsets, LENGTH(offsets), 4, (char*)&value, info.pHandle);
    }

    SHORT f3 = GetAsyncKeyState(VK_F3);
    if (f3) {
      unsigned char b1[] = { 0x78 };
      WriteProcessMemoryForce(info.pHandle, (LPVOID)0x23159f7, b1, sizeof(b1), NULL);
      unsigned char b2[] = { 0x88 };
      WriteProcessMemoryForce(info.pHandle, (LPVOID)0x23159c6, b2, sizeof(b2), NULL);
      Sleep(100);
      unsigned char b3[] = { 0x74 };
      WriteProcessMemoryForce(info.pHandle, (LPVOID)0x23159f7, b3, sizeof(b3), NULL);
      unsigned char b4[] = { 0x84 };
      WriteProcessMemoryForce(info.pHandle, (LPVOID)0x23159c6, b4, sizeof(b4), NULL);
    }
    Sleep(100);
  }
  CloseHandle(info.pHandle);
}