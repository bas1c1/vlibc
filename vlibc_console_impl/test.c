#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

#define WIDTH 30
#define HEIGHT 20

int main() {
	vlibc_canvas canvas = vlibc_console_alloc_canvas((VEC2D){WIDTH, HEIGHT});

	vlibc_filled_ellipse(&canvas, (vlibc_rgba){125, 125, 125, 255}, (VEC2D){0, 0}, 6, 2);
	vlibc_circle(&canvas, (vlibc_rgba){25, 25, 25, 255}, (VEC2D){8, 8}, 3);
	vlibc_rect(&canvas, (vlibc_rgba){200, 200, 200, 255}, (VEC2D){6, 6}, (VEC2D){16, 16});
	vlibc_put_pixel(&canvas, (vlibc_rgba){255, 255, 255, 255}, (VEC2D){0, 10});
	vlibc_filled_triangle(&canvas, (vlibc_rgba){255, 255, 255, 255}, (VEC2D){15, 0}, (VEC2D){8, 8}, (VEC2D){8, 0}, (VEC2D){0, 0});

	vlibc_console_flush_canvas(canvas);
}