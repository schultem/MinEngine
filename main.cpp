#include "mingw-std-threads-master/mingw.thread.h"
#include "engine/engine.h"
#include "game/game.h"

Engine engine(go::gameobject::game);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void WindowRefresh(HWND hwnd, Engine* engine)
{
  std::chrono::steady_clock::time_point last_updated = std::chrono::steady_clock::now();
  while (TRUE)
  {
    int dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-last_updated).count()/1000;
    int dt_requested = engine->Update(dt);
    last_updated = std::chrono::steady_clock::now();
    InvalidateRect(hwnd,NULL,TRUE);
    Sleep(dt_requested);
  }
}

int WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int nCmdShow)
{
  WNDCLASS wc;
  HWND hwnd;
  MSG msg;

  DWORD dwStyle=(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
  wc.style=CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc=WindowProc;
  wc.cbClsExtra=wc.cbWndExtra=0;
  wc.hInstance=hInst;
  wc.hIcon=LoadIcon(NULL,IDI_WINLOGO);
  wc.hCursor=LoadCursor(NULL,IDC_ARROW);
  wc.hbrBackground=(HBRUSH)COLOR_WINDOWFRAME;
  wc.lpszMenuName=NULL;
  wc.lpszClassName=engine.GetName().c_str();

  if (!RegisterClass(&wc))
    return 0;

  auto resolution = engine.GetResolution();
  RECT wr = {0, 0, resolution.x, resolution.y};
  AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

  hwnd = CreateWindow(wc.lpszClassName,wc.lpszClassName,
    dwStyle,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    wr.right - wr.left,
    wr.bottom - wr.top,
    NULL,NULL,hInst,NULL);

  if (!hwnd)
    return 0;

  ShowWindow(hwnd,nCmdShow);
  UpdateWindow(hwnd);
  std::thread(WindowRefresh,hwnd,&engine).detach();

  while (GetMessage(&msg,NULL,0,0) > 0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
    case WM_PAINT:
      PAINTSTRUCT ps;
      RECT wr;
      GetClientRect(hwnd,&wr);
      engine.Event( BeginPaint(hwnd,&ps) );
      EndPaint(hwnd,&ps);
      break;

    case WM_KEYDOWN:
      {
        go::keyinput ki(wparam);
        engine.Event( &ki );
        return DefWindowProc(hwnd, msg, wparam, lparam);
      }
  
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hwnd, msg, wparam, lparam);
  }
  return 0;
} 