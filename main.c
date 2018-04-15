#include <stdio.h>
#include <Windows.h>

int main () {
  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 29512);
  printf("%d", (int)handle);
  getchar();
}
