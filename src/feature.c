#include "feature.h"
#include "pureuse.c"

static struct Feature {
  struct ProcessInfo process;
  ADDRESS mycode;
  void (*init)();
} feature;

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

void killAll () {
  ADDRESS mycode = feature.mycode;
  HANDLE pHandle = feature.process.pHandle;
  struct HookPoint * loopPoint = getLoopPoint();
  hookFromFunc(pHandle, loopPoint, killthemall, killthemall_end, TRUE);
  Sleep(50);
  hookRecovery(pHandle, loopPoint);
}

void featureInit () {
  struct ProcessInfo info = getProcessByName("DNF.exe");
  feature.process = info;
  ADDRESS mycode = readyCodeToTarget(info.pHandle);
  feature.mycode = mycode;
}
