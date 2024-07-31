#define __VLIBC_IMPL__
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include "../vlibc.h"

#ifndef __VLIBC_CONSOLE__
#define __VLIBC_CONSOLE__

VLIBCDEF vlibc_canvas vlibc_console_alloc_canvas(vlibc_vec2d size);
VLIBCDEF int vlibc_console_to_grayscale(vlibc_rgba c);
VLIBCDEF char vlibc_console_character_grayscale(int gray_scale);
VLIBCDEF void vlibc_console_flush_canvas(vlibc_canvas canvas);
VLIBCDEF void vlibc_console_cursor_gotoxy(int x, int y);
VLIBCDEF void vlibc_console_clear_screen();

#endif

#ifdef __VLIBC_CONSOLE_IMPL__

vlibc_canvas vlibc_console_alloc_canvas(vlibc_vec2d size) {
	printf("width: %d height: %d\n", (int)size.x, (int)size.y);

	vlibc_uint32_t *graph = (vlibc_uint32_t*)malloc((size.x+1)*(size.y+1)*(sizeof(vlibc_uint32_t)));

	vlibc_canvas canvas = {
		.pixels = graph,
		.size = size
	};

	return canvas;
}

int vlibc_console_to_grayscale(vlibc_rgba c) {
	return (c.r + c.g + c.b)/3;
}

void vlibc_console_cursor_gotoxy(int x, int y) {
#if defined(_WIN32) || defined(_WIN64)
	COORD pos = {x, y};
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
#elif defined(__linux__) || defined(__unix__)
	printf("\033[%d;%dH",y+1,x+1);
#endif
}

void vlibc_console_clear_screen() {
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif
}

char vlibc_console_character_grayscale(int gray_scale) {
	if (gray_scale > 225) return '@';
	if (gray_scale > 200) return '%';
	if (gray_scale > 175) return '#';
	if (gray_scale > 150) return '*';
	if (gray_scale > 125) return '+';
	if (gray_scale > 100) return '=';
	if (gray_scale > 75) return '-';
	if (gray_scale > 50) return ':';
	if (gray_scale > 5) return '.';
	return ' ';
}

void vlibc_console_flush_canvas(vlibc_canvas canvas) {
	vlibc_console_clear_screen();
	for (int i = 0; i < canvas.size.x; i++) {
		for (int j = 0; j < canvas.size.y; j++) {
			vlibc_console_cursor_gotoxy(i, j);
			putchar(
				vlibc_console_character_grayscale(
					vlibc_console_to_grayscale(
						vlibc_hex_to_rgba(
							vlibc_get_pixel(&canvas, ((vlibc_vec2d){i, j}), 0)
						)
					)
				)
			);
		}
	}
	printf("\n");
}

#endif