#define __VLIBC_IMPL__
#define VLIBC_FONTS
#include "../vlibc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#ifndef __VLIBC_SDL__
#define __VLIBC_SDL__

VLIBCDEF vlibc_canvas vlibc_sdl_alloc_canvas(vlibc_vec2d size);
VLIBCDEF void vlibc_sdl_create_window(char *window_name, int width, int height);
VLIBCDEF void vlibc_sdl_start(void (*display_function)());
VLIBCDEF void vlibc_sdl_flush_canvas(vlibc_canvas *canvas);

#endif

#ifdef __VLIBC_SDL_IMPL__

static uint64_t __vlibc_sdl_time = 0;
static float vlibc_sdl_deltaTime = 0;

SDL_Event __vlibc_sdl_event;
SDL_Renderer *__vlibc_sdl_renderer;
SDL_Window *__vlibc_sdl_window;
SDL_Texture *__vlibc_sdl_framebuffer;

vlibc_canvas vlibc_sdl_alloc_canvas(vlibc_vec2d size) {
  printf("width: %d height: %d\n", (int)size.x, (int)size.y);

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

void vlibc_sdl_create_window(char *window_name, int width, int height) {
  SDL_Init(SDL_INIT_VIDEO);
  __vlibc_sdl_window = SDL_CreateWindow(
					window_name,
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					width, height,
					SDL_WINDOW_SHOWN);

  __vlibc_sdl_renderer = SDL_CreateRenderer(__vlibc_sdl_window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(__vlibc_sdl_renderer, 0, 0, 0, 0);
  SDL_RenderClear(__vlibc_sdl_renderer);
}

void vlibc_sdl_flush_canvas(vlibc_canvas *canvas) {
  SDL_Point tex_size;
  //SDL_QueryTexture(__vlibc_sdl_framebuffer, NULL, NULL, &tex_size.x, &tex_size.y);

  if (tex_size.x != canvas->size.x || tex_size.y != canvas->size.y) {
    SDL_DestroyTexture(__vlibc_sdl_framebuffer);
    __vlibc_sdl_framebuffer = SDL_CreateTexture(__vlibc_sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, canvas->size.x, canvas->size.y);
  }

  SDL_UpdateTexture(__vlibc_sdl_framebuffer , VLIBC_NULL, canvas->pixels, canvas->size.x * sizeof (uint32_t));

  //SDL_RenderClear(__vlibc_sdl_renderer);
  SDL_RenderCopy(__vlibc_sdl_renderer, __vlibc_sdl_framebuffer , VLIBC_NULL, VLIBC_NULL);

  SDL_RenderPresent(__vlibc_sdl_renderer);
}

void vlibc_sdl_start(void (*display_function)()) {
  clock_t current_ticks;
  uint64_t fps = 0;
  __vlibc_sdl_framebuffer = SDL_CreateTexture(__vlibc_sdl_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 1, 1);

  while (1) {
    if (SDL_PollEvent(&__vlibc_sdl_event) && __vlibc_sdl_event.type == SDL_QUIT)
      break;

    current_ticks = clock();

    display_function();

    vlibc_sdl_deltaTime = clock() - current_ticks;
    if(vlibc_sdl_deltaTime > 0)
      fps = CLOCKS_PER_SEC / vlibc_sdl_deltaTime;

    printf("FPS: %d\n", fps);

    if (__vlibc_sdl_time >= (uint64_t)-1)
      __vlibc_sdl_time = 0;
    __vlibc_sdl_time ++;
  }
  SDL_DestroyRenderer(__vlibc_sdl_renderer);
  SDL_DestroyWindow(__vlibc_sdl_window);
  SDL_Quit();
}

#endif
