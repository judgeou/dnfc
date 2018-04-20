#include <stdio.h>
#include <stdlib.h>
#include "baseAddress.h"
#include "useful.c"

void beginFunc () {}

#include "pureuse.c"

/**
 * 遍历场上的单位
 * @param zhenying 要排除的阵营
 * @param typemask 类别掩码
 * @param cb 对每个单位调用的call
 */
int allobj (int zhenying, int typemask, int * arr) {
  int renwu = getValue(人物基址);
  int count = 0;
  if (renwu != 0) {
    int bc = getValue(renwu + 0xBC);
    if (bc != 0) {
      int start = getValue(bc + 0xC0);
      int end = getValue(bc + 0xC4);
      int index = start;
      for (int index = start; index < end; index += 4) {
        int obj = getValue(index);
        int zy = getValue(obj + 阵营偏移);
        int type = getValue(obj + 类型偏移);
        if (zy == zhenying && ((type & typemask) == typemask)) {
          arr[count] = obj;
          count++;
        }
      }
      return count;
    } else {
      return count;
    }
  } else {
    return count;
  }
}

/**
 * 获取某个单位的当前血量
 * @param ptr
 */
int getHp (int ptr) {
  int hpValue;
  __asm
  {
    pushad
    mov ecx, ptr
    mov eax, [ecx]
    call [eax + 0x40C]
    mov hpValue, eax
    popad
  }
  return hpValue;
}

/**
 * 获取场上所有敌人的血量
 */
int getAllHp () {
  int objArr[50];
  int count = allobj(100, 0x11, objArr);
  int sumHp = 0;
  for (int i = 0; i < count; i++) {
    int hp = getHp(objArr[i]);
    sumHp += hp;
  }
  return sumHp;
}

/**
 * 扣血秒杀
 */
void killit_kouxue (int objptr) {
  __asm
  {
    pushad
    mov ecx, objptr
    push 0
    push 0
    push 0
    push ecx
    push 1
    push 0
    push 0
    mov eax, CALL_扣血
    call eax
    popad
  }
}

/**
 * 扣血秒杀全场
 */
void killthemall () {
  int objArr[50];
  int count = allobj(100, 0x11, objArr);
  for (int i = 0; i < count; i++) {
    killit_kouxue(objArr[i]);
  }
}

void endFunc () {}

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