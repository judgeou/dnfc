#include "../include/std.h"
#include "baseType.h"

struct HookPoint {
  ADDRESS address;
  unsigned char * originalBytes;
  int originalBytesSize;
  ADDRESS allocAddr;
  int allocSize;
};

/**
 * hook远程地址
 */
ADDRESS hook (HANDLE pHandle, struct HookPoint *hookpoint, unsigned char * code, int codeSize);

/**
 * 还原hook地址
 */
BOOL hookRecovery (HANDLE pHandle, struct HookPoint *hookpoint);

/**
 * hook远程地址，插入pushad popad
 */
ADDRESS hookKeepRegi (HANDLE pHandle, struct HookPoint *hookpoint, unsigned char * code, int codeSize);

/**
 * hook远程地址，使用本程序的函数代码
 */
ADDRESS hookFromFunc (HANDLE pHandle, struct HookPoint *hookpoint, void * begin, void * end, BOOL isKeepRegi);

/**
 * 取循环执行的HOOK点
 */
struct HookPoint * getLoopPoint ();

/**
 * 取伤害计算HOOK点
 */
struct HookPoint * getAllHpDmgPoint ();
