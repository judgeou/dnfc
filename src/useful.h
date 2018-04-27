#include "../include/std.h"
#include "baseType.h"

void printErrCode ();

struct ProcessInfo {
  HANDLE pHandle;
  DWORD pId;
};

/**
 * 多级指针读取内存值
 */
BOOL readPointerBuffer (
  ADDRESS address,
  int * offsets,
  int offsetsLen,
  int readSize,
  char * buffer,
  HANDLE pHandle
);

/**
 * 写入内存，无视保护，并且写入后恢复保护状态
 */
BOOL WriteProcessMemoryForce(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);

/**
 * 多级指针偏移写入
 */
BOOL writePointerBuffer (
  ADDRESS address,
  int * offsets,
  int offsetsLen,
  int writeSize,
  char * buffer,
  HANDLE pHandle
);

/**
 * 获取进程信息
 * @param name 进程名
 */
struct ProcessInfo getProcessByName(const char * name);

/**
 * 获取进程模块地址
 */
ADDRESS getModuleBaseAddr (char * name, DWORD pid);

/**
 * bytes转换成16进制字符串
 */
void toHex (unsigned char * arr, char * resultStr, int size);

/**
 * 读字节
 */
void readBytes (int address, unsigned char * arr, int size);

/**
 * 读取两个函数间的字节
 */
int readBytesBetweenTwoFunc (void * begin, void * end, unsigned char * byteArr);

/**
 * 读取两个函数间的字节，自行申请内存
 */
PUCHAR readBytesBetweenTwoFunc_alloc (void * begin, void * end, int * out_size);
