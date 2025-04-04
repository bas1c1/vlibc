#define __VLIBC_IMPL__
#define VLIBC_FONTS
#include "../vlibc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#error "System is not supported"
#endif

#ifndef __VLIBC_WINDOWS__
#define __VLIBC_WINDOWS__

VLIBCDEF vlibc_canvas vlibc_windows_alloc_canvas(vlibc_vec2d size);
VLIBCDEF void vlibc_windows_create_window(char *window_name, int width, int height);
VLIBCDEF void vlibc_windows_start(void (*display_function)());
VLIBCDEF void vlibc_windows_set_canvas(vlibc_canvas *canvas);
VLIBCDEF LRESULT CALLBACK __vlibc_windows_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);\

#endif

#ifdef __VLIBC_WINDOWS_IMPL__

vlibc_canvas *__vlibc_windows_canvas;

static int __vlibc_windows_width = 120;
static int __vlibc_windows_height = 120;

static HWND __vlibc_windows_hWnd = NULL;
static HBITMAP __vlibc_windows_bm = NULL;
static HDC __vlibc_windows_hdcc = NULL;

static vlibc_uint64_t __vlibc_windows_time = 0;
static float vlibc_windows_deltaTime = 0;

vlibc_canvas vlibc_windows_alloc_canvas(vlibc_vec2d size) {
  printf("width: %d height: %d\n", (int)size.x, (int)size.y);

  if (size.x < 120 || size.y < 120) {
    printf("%s\n", "Window size cannot be lower than 120x120");
    exit(-1);
  }

  vlibc_uint32_t *graph = (vlibc_uint32_t*)malloc((size.x+1)*(size.y+1)*(sizeof(vlibc_uint32_t)));

  vlibc_canvas canvas = {
    .pixels = graph,
    .offsize = size,
    .size = size,
    .offx = 0,
    .offy = 0
  };

  return canvas;
}

void vlibc_windows_set_canvas(vlibc_canvas *canvas) {
  __vlibc_windows_canvas = canvas;
}

void vlibc_windows_create_window(char *window_name, int width, int height) {
  WNDCLASS wnd = { 0 };

  wnd.lpfnWndProc = __vlibc_windows_proc;
  wnd.hInstance = GetModuleHandle(0);
  wnd.lpszClassName = (const char *)window_name;

  if (!RegisterClass(&wnd))
    return;

  if (width < 120 || height < 120) {
    printf("%s\n", "Window size cannot be lower than 120x120");
    exit(-1);
  }

  __vlibc_windows_width = width;
  __vlibc_windows_height = height;
  /*i know this is weird
    but idk how to fix that*/
  __vlibc_windows_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, wnd.lpszClassName, wnd.lpszClassName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width+20, height+40, NULL, NULL, GetModuleHandle(0), NULL);

  if (!__vlibc_windows_hWnd) 
    return;
}

void vlibc_windows_start(void (*display_function)()) {
  clock_t current_ticks;
  vlibc_uint64_t fps = 0;
  MSG msg = { 0 };

  ShowWindow(__vlibc_windows_hWnd, SW_SHOW);
  UpdateWindow(__vlibc_windows_hWnd);

  while (true) {
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
  break;
      }

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    current_ticks = clock();

    display_function();
    SetBitmapBits(__vlibc_windows_bm, __vlibc_windows_height * __vlibc_windows_width * sizeof(vlibc_uint32_t), (const void*)(__vlibc_windows_canvas->pixels));
    BitBlt(GetDC(__vlibc_windows_hWnd), 0, 0, __vlibc_windows_width, __vlibc_windows_height, __vlibc_windows_hdcc, 0, 0, SRCCOPY);

    vlibc_windows_deltaTime = clock() - current_ticks;
    if(vlibc_windows_deltaTime > 0)
      fps = CLOCKS_PER_SEC / vlibc_windows_deltaTime;

    printf("FPS: %d\n", fps);

    if (__vlibc_windows_time >= (vlibc_uint64_t)-1)
      __vlibc_windows_time = 0;
    __vlibc_windows_time ++;
  }
}

LRESULT CALLBACK __vlibc_windows_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg){
  case WM_CREATE:
    HDC hWinDC = GetDC(hwnd);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPCOREHEADER);
    bmi.bmiHeader.biWidth = __vlibc_windows_width;
    bmi.bmiHeader.biHeight = -__vlibc_windows_height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    __vlibc_windows_hdcc = CreateCompatibleDC(hWinDC);
    __vlibc_windows_bm = CreateCompatibleBitmap(hWinDC, __vlibc_windows_width, __vlibc_windows_height); 
    SetBitmapBits(__vlibc_windows_bm, __vlibc_windows_height * __vlibc_windows_width * sizeof(vlibc_uint32_t), (const void*)(__vlibc_windows_canvas->pixels));
      
    SelectObject(__vlibc_windows_hdcc, __vlibc_windows_bm);
    ReleaseDC(hwnd, hWinDC);
    break;

  case WM_DESTROY:
    DeleteDC(__vlibc_windows_hdcc);
    DeleteObject(__vlibc_windows_bm);
    PostQuitMessage(0);
    break;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

#endif
