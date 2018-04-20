#pragma comment(lib, "user32")
#include <stdio.h>
#include <Windows.h>
#include "useful.c"
#include "pureuse.c"

int main () {
  unsigned char * byteArr = (unsigned char *)malloc(1024);
  int byteSize = readBytesBetweenTwoFunc(beginFunc, endFunc, byteArr);

  struct ProcessInfo info = getProcessByName("DNF.exe");
  ADDRESS mycode = (ADDRESS)VirtualAllocEx(info.pHandle, NULL, byteSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  BOOL r1 = WriteProcessMemoryForce(info.pHandle, (LPVOID)mycode, byteArr, byteSize, NULL);
  int killthemallAddr = mycode + ((int)killthemall - (int)beginFunc);

  if (mycode && r1) {
    printf("write %d bytes %x\n", byteSize, mycode);
  }

  struct HookPoint loopPoint;
  loopPoint.address = HOOK_LOOP;
  unsigned char originalBytes[] = { 0x8B, 0x90, 0x14, 0x06, 00, 00 };
  loopPoint.originalBytes = originalBytes;
  loopPoint.originalBytesSize = 6;

  unsigned char code[] = { 0x60, 0xB8, 0x00, 00, 00, 00, 0xFF, 0xD0, 0x61 };
  *(int*)&code[2] = killthemallAddr;

  while (info.pHandle) {
    SHORT s = GetAsyncKeyState(VK_F1);
    if (s) {
      ADDRESS codeAddr = hook(info.pHandle, loopPoint, code, sizeof(code));
      printf("kill %x\n", codeAddr);
      Sleep(50);
      hookRecovery(info.pHandle, loopPoint, codeAddr);
    }

    SHORT f2 = GetAsyncKeyState(VK_F2);
    if (f2) {
      int offsets[] = { 0xc0c };
      int value = 741741;
      writePointerBuffer(SSS_ADDR, offsets, LENGTH(offsets), 4, (char*)&value, info.pHandle);
    }
    Sleep(100);
  }
  CloseHandle(info.pHandle);
}