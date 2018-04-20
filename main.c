#include <stdio.h>
#include "useful.c"
#include <Windows.h>

int main () {
  struct ProcessInfo info = getProcessByName("TIM.exe");
  struct HookPoint hp1;
  hp1.address = 0x10CD0000;
  unsigned char originalBytes[] = { 0x8B, 0x90, 0x38, 0x06, 00, 00 };
  hp1.originalBytes = originalBytes;
  hp1.originalBytesSize = sizeof(originalBytes);
  unsigned char hookcode[] = { 0x60, 0xB8, 0x01, 00, 00, 00, 0xFF, 0xD0, 0x61 };
  ADDRESS jmpAddr = hook(info.pHandle, hp1, hookcode, sizeof(hookcode));
  printf("%x", jmpAddr);
  getchar();

  BOOL r = hookRecovery(info.pHandle, hp1, jmpAddr);
  printf("%d", r);
}
