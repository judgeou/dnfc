#include <stdio.h>
#include <stdlib.h>
#include "baseAddress.h"
#include "useful.c"
#include "pureuse.c"

void cescript (char * str, int strsize) {
  unsigned char * byteArr = (unsigned char *)malloc(1024);
  int byteSize = readBytesBetweenTwoFunc(beginFunc, endFunc, byteArr);
  char * hexStr = (char *)malloc(byteSize * 3 + 1);
  toHex(byteArr, hexStr, byteSize);

  sprintf_s(str, strsize, "\
alloc(code, 4096)\n\
registerSymbol(code)\n\
code:\n\
db %s\n\
define(getAllHp, code+%x)\n\
registerSymbol(getAllHp)\n\
define(killthemall, code+%x)\n\
registerSymbol(killthemall)\n\
", hexStr, (int)getAllHp - (int)beginFunc, (int)killthemall - (int)beginFunc);
}

int main () {
  char str[4096];
  cescript(str, 4096);
  printf("%s", str);
}