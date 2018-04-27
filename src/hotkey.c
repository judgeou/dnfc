#include "../include/std.h"
#include "hotkey.h"

struct keyNode {
  int vKey;
  void (*func)();
  void (*aginaFunc)();
  int pressCount;
  struct keyNode * next;
};

static struct keyNode * beginKeyNode;
static struct keyNode * lastKeyNode;

void bindKey (int vKey, void * func, void * aginaFunc) {
  struct keyNode * newNode = malloc(sizeof(struct keyNode));
  newNode->vKey = vKey;
  newNode->func = func;
  newNode->aginaFunc = aginaFunc;
  newNode->pressCount = 0;
  newNode->next = 0;

  if (lastKeyNode) {
    lastKeyNode->next = newNode;
    lastKeyNode = newNode;
  } else {
    beginKeyNode = newNode;
    lastKeyNode = newNode;
  }
}

void startSyncListenKey () {
  while(1) {
    struct keyNode * node = beginKeyNode;
    while (node) {
      SHORT kcode = GetAsyncKeyState(node->vKey);
      if (kcode & 0x0001) {
        printf("%x\n", kcode);
        if (node->pressCount % 2 == 0) {
          node->func();
        } else {
          if (node->aginaFunc) {
            node->aginaFunc();
          } else {
            node->func();
          }
        }
        node->pressCount++;
      }

      node = node->next;
    }

    Sleep(50);
  }
}