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