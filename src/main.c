#include "../include/std.h"
#include "hotkey.h"
#include "feature.h"

int main () {
  featureInit();
  bindKey(VK_F12, miaosha, miaoshaRe);
  // bindKey(VK_F11, killAll, NULL);
  startSyncListenKey();
}