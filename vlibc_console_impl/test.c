#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

#define WIDTH 300
#define HEIGHT 200

uint32_t frag_shader_f(VEC2D pos, vlibc_rgba color) {
	vlibc_vertex v2, v1, v0;
	v0.pos = (VEC2D){150, 0};
	v0.col = (vlibc_rgba){1, 0, 0, 1};

	v1.pos = (VEC2D){0, 190};
	v1.col = (vlibc_rgba){0, 1, 0, 1};

	v2.pos = (VEC2D){290, 190};
	v2.col = (vlibc_rgba){0, 0, 1, 1};

	float area = vlibc_edge(v2.pos, v1.pos, v0.pos);

	float e0 = vlibc_edge(v2.pos, v1.pos, pos);
	float e1 = vlibc_edge(v0.pos, v2.pos, pos);
	float e2 = vlibc_edge(v1.pos, v0.pos, pos);

	float w0 = e0 / area;
	float w1 = e1 / area;
	float w2 = e2 / area;

	float r =
		  w0 * v0.col.r
		+ w1 * v1.col.r
		+ w2 * v2.col.r;

	float g =
		  w0 * v0.col.g
		+ w1 * v1.col.g
		+ w2 * v2.col.g;

	float b =
		  w0 * v0.col.b
		+ w1 * v1.col.b
		+ w2 * v2.col.b;

	uint8_t red = r * 255;
	uint8_t green = g * 255;
	uint8_t blue = b * 255;
	uint8_t alpha = 255;


	return vlibc_rgba_to_hex((vlibc_rgba) {
		.r = red,
		.g = green,
		.b = blue,
		.a = 255
	});
}

vlibc_canvas canvas;

int main(int argc, char *argv[]) {
	vlibc_fragment_shader_t frag_shader = vlibc_create_fragment_shader(frag_shader_f);

	canvas = vlibc_console_alloc_canvas((VEC2D){WIDTH, HEIGHT});

	/*vlibc_filled_ellipse(&canvas, (vlibc_rgba){125, 125, 125, 255}, (VEC2D){0, 0}, 6, 2);
	vlibc_circle(&canvas, (vlibc_rgba){25, 25, 25, 255}, (VEC2D){8, 8}, 3);
	vlibc_rect(&canvas, (vlibc_rgba){200, 200, 200, 255}, (VEC2D){6, 6}, (VEC2D){16, 16});*/
	//vlibc_put_pixel(&canvas, (vlibc_rgba){255, 255, 255, 255}, (VEC2D){i, 10}, &frag_shader);

	vlibc_console_flush_canvas(canvas);
}