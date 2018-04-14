#include <stdlib.h>
#include <string.h>

void nothing () {
}

int getValue (int address) {
  return *(int*)address;
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

void readBytes (int address, unsigned char * arr, int size) {
  for (int i = 0; i < size; i++) {
    char byte = *(unsigned char*)address;
    arr[i] = byte;
    address++;
  }
}

int getFunOffset (int funcAddr) {
  int firstFun = nothing;
  return funcAddr - firstFun;
}
