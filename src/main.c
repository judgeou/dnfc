#include "../include/std.h"
#include "hotkey.h"
#include "feature.h"

int main () {
  featureInit();
  bindKey(VK_F12, miaosha, miaoshaRe);
  bindKey(VK_F11, miaosha999, NULL);
  bindKey(VK_F10, comeon, NULL);
  // bindKey(VK_F11, killAll, NULL);
  startSyncListenKey();
}