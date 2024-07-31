#define __VLIBC_IMPL__
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include "../vlibc.h"

#ifndef __VLIBC_SDL__
#define __VLIBC_SDL__

VLIBCDEF vlibc_canvas vlibc_sdl_alloc_canvas(vlibc_vec2d size);
VLIBCDEF void vlibc_sdl_create_window(char *window_name, int width, int height);
VLIBCDEF void vlibc_sdl_start(void (*display_function)());
VLIBCDEF void vlibc_sdl_flush_canvas(vlibc_canvas canvas);

#endif

#ifdef __VLIBC_SDL_IMPL__

SDL_Event __vlibc_sdl_event;
SDL_Renderer *__vlibc_sdl_renderer;
SDL_Window *__vlibc_sdl_window;

vlibc_canvas vlibc_sdl_alloc_canvas(vlibc_vec2d size) {
	printf("width: %d height: %d\n", (int)size.x, (int)size.y);

	vlibc_uint32_t *graph = (vlibc_uint32_t*)malloc((size.x+1)*(size.y+1)*(sizeof(vlibc_uint32_t)));

	vlibc_canvas canvas = {
		.pixels = graph,
		.size = size
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

void vlibc_sdl_flush_canvas(vlibc_canvas canvas) {
	SDL_RenderClear(__vlibc_sdl_renderer);

	/*i know that this is slow, but it's the only working code*/

	for (int i = 0; i < canvas.size.x; i++) {
		for (int j = 0; j < canvas.size.y; j++) {
			vlibc_rgba col = vlibc_hex_to_rgba( vlibc_get_pixel(&canvas, ((vlibc_vec2d){i, j}), 0) );
			SDL_SetRenderDrawColor(__vlibc_sdl_renderer, col.r, col.g, col.b, col.a);
			SDL_RenderDrawPoint(__vlibc_sdl_renderer, i, j);
		}
	}

	SDL_RenderPresent(__vlibc_sdl_renderer);
}

void vlibc_sdl_start(void (*display_function)()) {
	while (1) {
		if (SDL_PollEvent(&__vlibc_sdl_event) && __vlibc_sdl_event.type == SDL_QUIT)
			break;

		display_function();
	}
	SDL_DestroyRenderer(__vlibc_sdl_renderer);
	SDL_DestroyWindow(__vlibc_sdl_window);
	SDL_Quit();
}

#endif