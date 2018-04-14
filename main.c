#include <stdio.h>
#include "baseAddress.h"
#include "useful.h"
#include <Windows.h>
#include <string.h>

/**
 * 遍历场上的单位
 * @param zhenying 阵营
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
    sumHp += getHp(objArr[i]);
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
  int firstFun = (int)nothing;
  int size = (int)endFunc - firstFun + 1;
  unsigned char byteArr[size];
  char hexStr[size * 3 + 1];
  readBytes(firstFun, byteArr, size);
  toHex(byteArr, hexStr, size);

  sprintf_s(str, strsize, "\
alloc(code, 4096)\n\
registerSymbol(code)\n\
code:\n\
db %s\n\
define(getAllHp, code+%x)\n\
registerSymbol(getAllHp)\n\
define(killthemall, code+%x)\n\
registerSymbol(killthemall)\n\
", hexStr, getAllHp - firstFun, killthemall - firstFun);
}

int main () {
  char str[2000];
  cescript(str, 2000);
  printf("%s", str);
  getchar();
  return 0;
}
