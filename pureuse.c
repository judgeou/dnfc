#include "baseAddress.h"

void beginFunc () {}

int getValue (int address) {
  return *(int*)address;
}

void readBytes (int address, unsigned char * arr, int size) {
  for (int i = 0; i < size; i++) {
    char byte = *(unsigned char*)address;
    arr[i] = byte;
    address++;
  }
}

int readBytesBetweenTwoFunc (void (*beginFunc)(), void (*endFunc)(), unsigned char * byteArr) {
  int begin = (int)beginFunc;
  int end = (int)endFunc;
  int size = end - begin + 1;
  readBytes(begin, byteArr, size);
  return size;
}

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
        if ((zy == zhenying || zy == 101) && ((type & typemask) == typemask)) {
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

void killthemall_end () {}

void endFunc () {}
