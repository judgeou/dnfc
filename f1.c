#pragma comment(lib, "user32")
#include <stdio.h>
#include <Windows.h>
#include "useful.c"
#include "pureuse.c"

int main () {
  unsigned char * byteArr = (unsigned char *)malloc(1024);
  int byteSize = readBytesBetweenTwoFunc(beginFunc, endFunc, byteArr);

  struct ProcessInfo info = getProcessByName("DNF.exe");
  ADDRESS mycode = (ADDRESS)VirtualAllocEx(info.pHandle, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

  if (mycode) {
    printf("已写入 %d 字节，%x", byteSize, mycode);
  }

  while (info.pHandle) {
    SHORT s = GetAsyncKeyState(VK_F1);
    if (s) {
      printf("Hello");
      char jmp[] = HOOK_JMP;
      char re[] = HOOK_RE;
      BOOL r1 = WriteProcessMemoryForce(info.pHandle, (LPVOID)HOOK_LOOP, jmp, sizeof(jmp), NULL);
      Sleep(100);
      BOOL r2 = WriteProcessMemoryForce(info.pHandle, (LPVOID)HOOK_LOOP, re, sizeof(re), NULL);
      printf("%d %d\n", r1, r2);
    }
    Sleep(100);
  }
  CloseHandle(info.pHandle);
}