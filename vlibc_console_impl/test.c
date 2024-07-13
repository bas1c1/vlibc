#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

#define WIDTH 30
#define HEIGHT 30

uint32_t frag_shader_f(vlibc_vertex *vertices, int num_of_vertices, VEC2D pos, vlibc_rgba color) {
	return vlibc_rgba_to_hex(color);
}

int main(int argc, char *argv[]) {
	vlibc_fragment_shader_t frag_shader = vlibc_create_fragment_shader(frag_shader_f);

	vlibc_canvas canvas = vlibc_console_alloc_canvas((VEC2D){WIDTH, HEIGHT});

	vlibc_vertex v6, v5, v4, v3, v2, v1, v0;
	v0.pos = (VEC2D){0, 0};
	v0.col = (vlibc_rgba){255, 0, 0, 255};

	v1.pos = (VEC2D){19, 0};
	v1.col = (vlibc_rgba){0, 255, 0, 255};

	v2.pos = (VEC2D){0, 19};
	v2.col = (vlibc_rgba){0, 0, 255, 255};

	v3.pos = (VEC2D){19, 19};
	v3.col = (vlibc_rgba){255, 255, 0, 255};

	v4.pos = (VEC2D){29, 29};
	v4.col = (vlibc_rgba){255, 255, 0, 255};

	v5.pos = (VEC2D){29, 19};
	v5.col = (vlibc_rgba){255, 0, 255, 255};

	vlibc_vertex vertices[6] = {v0, v1, v2, v3, v4, v5};

	vlibc_filled_figure(&canvas, (vlibc_rgba){255, 255, 255, 255}, (VEC2D){0, 0}, vertices, 6, &frag_shader);

	vlibc_console_flush_canvas(canvas);
}