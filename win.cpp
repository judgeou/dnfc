#ifndef UNICODE
#define UNICODE
#endif
extern "C" {
  #include "include/std.h"
  #include "src/feature.h"
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateChilds (HWND hWnd, HINSTANCE hInstance);
DWORD WINAPI showMsg (const wchar_t * msg);
HANDLE CALLBACK showMsgAsync (const wchar_t * msg);
void registerKeys (HWND hwnd);

void registerKeys (HWND hwnd) {
  RegisterHotKey(hwnd, 1, MOD_ALT | MOD_NOREPEAT, VK_F12);
  RegisterHotKey(hwnd, 2, MOD_CONTROL | MOD_NOREPEAT, VK_F12);
  RegisterHotKey(hwnd, 3, MOD_ALT | MOD_NOREPEAT, VK_F11);
  RegisterHotKey(hwnd, 4, MOD_ALT | MOD_NOREPEAT, VK_F10);
}

void hotKeyProc (UINT vk, UINT fu) {
  if (vk == VK_F12 & fu == MOD_ALT) {
    miaosha();
    showMsgAsync(L"大杀四方");
  } else if (vk == VK_F11 & fu == MOD_ALT) {
    miaosha999();
    showMsgAsync(L"999伤害");
  } else if (vk == VK_F10 & fu == MOD_ALT) {
    SSS();
    showMsgAsync(L"SSS");
  } else if (vk == VK_F12 & fu == MOD_CONTROL) {
    miaoshaRe();
    showMsgAsync(L"不秒杀了");
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const wchar_t CLASS_NAME[]  = L"君のごと大好き";
  
  WNDCLASS wc = { };

  wc.lpfnWndProc   = WindowProc;
  wc.hInstance     = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window.

  HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    CLASS_NAME,                     // Window class
    L"君のごと大好き",    // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, 300, 100,

    NULL,       // Parent window    
    NULL,       // Menu
    hInstance,  // Instance handle
    NULL        // Additional application data
  );

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  registerKeys(hwnd);

  // Run the message loop.

  MSG msg = { };
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
    case WM_CREATE: {
      featureInit();
      showMsgAsync(L"绅士力量已就绪");
      return 0;
    }
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_HOTKEY: {
      UINT fu = (UINT)LOWORD(lParam);
      UINT vk = (UINT)HIWORD(lParam);
      hotKeyProc(vk, fu);
      return 0;
    }
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

DWORD WINAPI showMsg (const wchar_t * msg) {
  HWND hwnd = CreateWindow(
    L"static",
    msg,
    WS_DISABLED,
    10,
    10,
    300,
    1,
    NULL,
    NULL,
    NULL,
    NULL
  );
  SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 300, 1,
    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
  Sleep(1500);
  DestroyWindow(hwnd);
  return 0;
}

HANDLE CALLBACK showMsgAsync (const wchar_t * msg) {
  return CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)showMsg, (LPVOID)msg, 0, NULL);
}