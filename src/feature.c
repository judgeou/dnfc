#include "feature.h"
#include "pureuse.c"

static struct Feature {
  struct ProcessInfo process;
  ADDRESS mycode;
  void (*init)();
} feature;
static UCHAR hookwapper[] = { 0x60, 0xB8, 0x00, 00, 00, 00, 0xFF, 0xD0, 0x61 };

ADDRESS readyCodeToTarget (HANDLE pHandle) {
  int byteSize = (int)endFunc - (int)beginFunc + 1;
  PUCHAR byteArr = (PUCHAR)beginFunc;
  ADDRESS mycode = (ADDRESS)VirtualAllocEx(pHandle, NULL, byteSize, MEM_COMMIT, PAGE_EXECUTE);
  if (mycode) {
    BOOL r = WriteProcessMemoryForce(pHandle, (LPVOID)mycode, byteArr, byteSize, NULL);
    printf("write %d bytes %x\n", byteSize, mycode);
    return r? mycode: FALSE;
  } else {
    return FALSE;
  }
}

PUCHAR hookjmpBytes (void * func) {
  PUCHAR bytes = malloc(sizeof(hookwapper));
  memcpy(bytes, hookwapper, sizeof(hookwapper));
  int addr = feature.mycode + ((int)func - (int)beginFunc);
  *(int*)(bytes + 2) = addr;
  return bytes;
}

void killAll () {
  HANDLE pHandle = feature.process.pHandle;
  struct HookPoint * loopPoint = getLoopPoint();
  PUCHAR code = hookjmpBytes(killthemall);
  ADDRESS r = hook(pHandle, loopPoint, code, sizeof(hookwapper));
  printf("ohhhh! %x\n", r);
  Sleep(50);
  hookRecovery(pHandle, loopPoint);
}

void miaosha () {
  HANDLE pHandle = feature.process.pHandle;
  struct HookPoint * dmgPoint = getAllHpDmgPoint();
  PUCHAR code = hookjmpBytes(hookcode_allhpdmg);
  ADDRESS r = hook(pHandle, dmgPoint, code, sizeof(hookwapper));
  printf("one hit kill ON %x\n", r);
}

void miaoshaRe () {
  HANDLE pHandle = feature.process.pHandle;
  struct HookPoint * dmgPoint = getAllHpDmgPoint();
  hookRecovery(pHandle, dmgPoint);
  printf("one hit kill OFF\n");
}

void miaosha999 () {
  HANDLE pHandle = feature.process.pHandle;
  struct HookPoint * dmgPoint = getAllHpDmgPoint();
  PUCHAR code = hookjmpBytes(hookcode_999dmg);
  ADDRESS r = hook(pHandle, dmgPoint, code, sizeof(hookwapper));
  printf("99999999 ON %x\n", r);
}

void featureInit () {
  struct ProcessInfo info = getProcessByName("DNF.exe");
  feature.process = info;
  ADDRESS mycode = readyCodeToTarget(info.pHandle);
  feature.mycode = mycode;
}
