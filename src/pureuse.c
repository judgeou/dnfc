#include "baseAddress.h"

void beginFunc () {}

int getValue (int address) {
  return *(int*)address;
}

void setValue (int address, int value) {
  *(int*)address = value;
}

int getPointerValue (int base, int * offsets, int offsetsLen) {
  int start = getValue(base);
  if (offsetsLen == 0) {
    return start;
  } else {
    for (int i = 0; i < offsetsLen; i++) {
      int ptrAddr = start + offsets[i];
      if (i == offsetsLen - 1) {
        return getValue(ptrAddr);
      } else {
        start = getValue(ptrAddr);
      }
    }
    return 0;
  }
}

char setPointerValue (int base, int * offsets, int offsetsLen, int value) {
  int start = getValue(base);
  if (offsetsLen == 0) {
    setValue(base, value);
    return 0;
  } else {
    for (int i = 0; i < offsetsLen; i++) {
      int ptrAddr = start + offsets[i];
      if (i == offsetsLen - 1) {
        setValue(ptrAddr, value);
        return 0;
      } else {
        start = getValue(ptrAddr);
      }
    }
    return 1;
  }
}

float getPointerValueF (int base, int * offsets, int offsetsLen) {
  int r = getPointerValue(base, offsets, offsetsLen);
  return *(float*)&r;
}

char setPointerValueF (int base, int * offsets, int offsetsLen, float value) {
  int intValue = *(int*)&value;
  return setPointerValue(base, offsets, offsetsLen, intValue);
}

/**
 * 遍历场上的单位
 * @param zhenying 要排除的阵营
 * @param typemask 类别掩码
 * @param cb 对每个单位调用的call
 */
int allobj (int zhenying, int typemask, int * arr) {
  int renwu = getValue(ADDR_PLAYER);
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
        if ((zy == zhenying || zy == 101 || zy == 75 ) 
          && ((type & typemask) == typemask)) {
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
    mov eax, CALL_SETHP
    call eax
    popad
  }
}

/**
 * 扣血秒杀全场
 */
void killthemall () {
  int objArr[100];
  int count = allobj(100, 0x11, objArr);
  for (int i = 0; i < count; i++) {
    killit_kouxue(objArr[i]);
  }
}

void killthemall_end () {}

void hookcode_comeon () {
  int distance;
  int r;
  __asm {
    mov distance, 100
    mov r, 2
  }

  int offsetX[] = { OFFSET_PLAYER_X };
  float playerX = getPointerValueF(ADDR_PLAYER, offsetX, 1);
  int offsetY[] = { OFFSET_PLAYER_Y };
  float playerY = getPointerValueF(ADDR_PLAYER, offsetY, 1);
  int offsetZ[] = { OFFSET_PLAYER_Z };
  float playerZ = getPointerValueF(ADDR_PLAYER, offsetZ, 1);

  int offsetFace[] = { OFFSET_PLAYER_FACE };
  int face = getPointerValue(ADDR_PLAYER, offsetFace, 1);
  int faceFlag = (face == 0 ? -1 : 1);
  distance = distance * faceFlag;
  float startPointX = playerX + distance;
  float startPointY = playerY - r;

  int objArr[100];
  int count = allobj(100, 0x11, objArr);
  int index = 0;
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (index < count) {
        int obj = objArr[index];
        index++;

        float x = startPointX + (col * r * faceFlag);
        float y = startPointY + (row * r);

        int posBase = obj + 0xAC;
        int ox[] = { 0x10 };
        setPointerValueF(posBase, ox, 1, x);
        int oy[] = { 0x14 };
        setPointerValueF(posBase, oy, 1, y);
        int oz[] = { 0x18 };
        setPointerValueF(posBase, oz, 1, playerZ);

      }
    }
  }
}

void hookcode_allhpdmg () {
  int obj;
  __asm
  {
    mov eax, [ebp + 0xc]
    mov obj, eax
  }
  int zy = getValue(obj + 阵营偏移);
  int type = getValue(obj + 类型偏移);
  if ((type & 0x11) == 0x11) {
    int dmg;
    if (zy == 0) {
      dmg = 1;
    } else {
      hookcode_comeon();
      dmg = getAllHp();
    }
    __asm {
      cvtsi2ss xmm0, dmg
    }
  }
}

void hookcode_allhpdmg_end () {}

void hookcode_999dmg () {
  int obj;
  __asm
  {
    mov eax, [ebp + 0xc]
    mov obj, eax
  }
  int zy = getValue(obj + 阵营偏移);
  int type = getValue(obj + 类型偏移);
  if ((type & 0x11) == 0x11) {
    int dmg;
    if (zy == 0) {
      dmg = 1;
    } else {
      dmg = 100000000;
    }
    __asm {
      cvtsi2ss xmm0, dmg
    }
  }
}

void hookcode_growDmg () {
  int obj;
  float originDmg;
  __asm
  {
    mov eax, [ebp + 0xc]
    mov obj, eax
    movss originDmg, xmm0 
  }
  int zy = getValue(obj + 阵营偏移);
  int type = getValue(obj + 类型偏移);
  if ((type & 0x11) == 0x11) {
    int dmg;
    if (zy == 0) {
      dmg = 1;
    } else {
      int vesp;
      __asm {
        mov vesp, esp
      }
      int * mul;
      int * preObj;
      mul = (int*)(vesp-0x30000);
      preObj = (int*)(vesp-0x30004);

      if (*mul == 0) {
        *mul = 1;
      }
      dmg = originDmg * (*mul);
      if (obj != *preObj) {
        (*mul)+=5;
        *preObj = obj;
      }
    }
    __asm {
      cvtsi2ss xmm0, dmg
    }
  }
}

void endFunc () {}
