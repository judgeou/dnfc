#include "../include/std.h"
#include "baseType.h"
#include "baseAddress.h"
#include "useful.h"
#include "hook.h"

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
    free(rCode);
    // 写入跳转
    unsigned char jmpBytes[5];
    jmpBytes[0] = 0xE9;
    *(int*)&jmpBytes[1] = jmpAddr - hookpoint->address - 5;
    BOOL r = WriteProcessMemoryForce(pHandle, (LPVOID)hookpoint->address, jmpBytes, 5, NULL);
    return r? jmpAddr: 0;
  } else {
    free(rCode);
    return FALSE;
  }
}

ADDRESS hookKeepRegi (HANDLE pHandle, struct HookPoint *hookpoint, unsigned char * code, int codeSize) {
  // 多一个字节，头部写入pushad，然后popad覆盖掉尾部的ret
  int writeCodeSize = codeSize + 1;
  unsigned char * writeCode = (PUCHAR)malloc(writeCodeSize);
  writeCode[0] = 0x60;
  memcpy(writeCode + 1, code, codeSize);
  writeCode[writeCodeSize - 1] = 0x61;
  hookpoint->allocSize = writeCodeSize;
  ADDRESS r = hook(pHandle, hookpoint, writeCode, writeCodeSize);
  free(writeCode);
  return r;
}

ADDRESS hookFromFunc (HANDLE pHandle, struct HookPoint *hookpoint, void * begin, void * end, BOOL isKeepRegi) {
  int funcSize = (int)end - (int)begin;
  PUCHAR codeBytes = (PUCHAR)begin;
  ADDRESS r;
  if (isKeepRegi) {
    r = hookKeepRegi(pHandle, hookpoint, codeBytes, funcSize);
  } else {
    r = hook(pHandle, hookpoint, codeBytes, funcSize);
  }
  return r;
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
    BOOL r = VirtualProtectEx(pHandle, (LPVOID)hookpoint->allocAddr, hookpoint->allocSize, PAGE_NOACCESS, &old);
    if (!r) {
      printErrCode();
    }
    return r;
  } else {
    return FALSE;
  }
}

static unsigned char loopPointOB[] = { 0x8B, 0x90, 0x14, 0x06, 00, 00 };
static struct HookPoint * loopPoint;
struct HookPoint * getLoopPoint () {
  if (loopPoint) {
    return loopPoint;
  } else {
    loopPoint = malloc(sizeof(struct HookPoint));
    loopPoint->address = HOOK_LOOP;
    loopPoint->originalBytes = loopPointOB;
    loopPoint->originalBytesSize = sizeof(loopPointOB);
    loopPoint->allocAddr = 0;
    loopPoint->allocSize = 0;
    return loopPoint;
  }
}

static unsigned char getAllHpDmgOB[] = { 0xF3, 0x0F, 0x11, 0x45, 0x08 };
static struct HookPoint * allHpDmgPoint;
struct HookPoint * getAllHpDmgPoint () {
  if (allHpDmgPoint) {
    return allHpDmgPoint;
  } else {
    allHpDmgPoint = malloc(sizeof(struct HookPoint));
    allHpDmgPoint->address = ADDR_DMGCALC;
    allHpDmgPoint->originalBytes = getAllHpDmgOB;
    allHpDmgPoint->originalBytesSize = sizeof(getAllHpDmgOB);
    allHpDmgPoint->allocAddr = 0;
    allHpDmgPoint->allocSize = 0;
    return allHpDmgPoint;
  }
}
