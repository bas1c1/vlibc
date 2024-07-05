#define __VLIBC_IMPL__
#include <stdio.h>
#include <stdlib.h>
#include "../vlibc.h"

#ifndef __VLIBC_CONSOLE__
#define __VLIBC_CONSOLE__

vlibc_canvas vlibc_console_alloc_canvas(VEC2D size);
int vlibc_console_to_grayscale(vlibc_rgba c);
char vlibc_console_character_grayscale(int gray_scale);
void vlibc_console_flush_canvas(vlibc_canvas canvas);

#endif

#ifdef __VLIBC_CONSOLE_IMPL__

vlibc_canvas vlibc_console_alloc_canvas(VEC2D size) {
	vlibc_swap(&size.x, &size.y);

	uint32_t *graph = (uint32_t*)malloc((size.x+1)*(size.y+1)*(sizeof(uint32_t)));

	vlibc_canvas canvas = {
		.pixels = graph,
		.size = size
	};

	return canvas;
}

int vlibc_console_to_grayscale(vlibc_rgba c) {
	return (c.r + c.g + c.b)/3;
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
	for (int i = 0; i < canvas.size.x; i++) {
		for (int j = 0; j < canvas.size.y; j++) {
			putchar(
				vlibc_console_character_grayscale(
					vlibc_console_to_grayscale(
						vlibc_hex_to_rgba(
							vlibc_get_pixel(&canvas, ((VEC2D){i, j}), 0)
						)
					)
				)
			);
		}
		putchar('\n');
	}
}

#endif