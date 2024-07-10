#define __VLIBC_SDL_IMPL__
#include "vlibc_sdl.h"

#define WIDTH 400
#define HEIGHT 400

uint32_t frag_shader_f(vlibc_vertex *vertices, int num_of_vertices, VEC2D pos, vlibc_rgba color) {
	return vlibc_rgba_to_hex(color);
}

vlibc_fragment_shader_t frag_shader;
vlibc_canvas canvas;

void display() {
	vlibc_vertex v6, v5, v4, v3, v2, v1, v0;
	v0.pos = (VEC2D){0, 0};
	v0.col = (vlibc_rgba){255, 0, 0, 255};

	v1.pos = (VEC2D){190, 0};
	v1.col = (vlibc_rgba){0, 255, 0, 255};

	v2.pos = (VEC2D){0, 190};
	v2.col = (vlibc_rgba){0, 0, 255, 255};

	v3.pos = (VEC2D){190, 190};
	v3.col = (vlibc_rgba){255, 255, 0, 255};

	v4.pos = (VEC2D){290, 290};
	v4.col = (vlibc_rgba){255, 255, 0, 255};

	v5.pos = (VEC2D){290, 190};
	v5.col = (vlibc_rgba){255, 0, 255, 255};

	v6.pos = (VEC2D){390, 0};
	v6.col = (vlibc_rgba){255, 255, 255, 255};

	vlibc_vertex vertices[] = {v0, v1, v2, v3, v4, v5, v6};

	vlibc_filled_figure(&canvas, (vlibc_rgba){255, 255, 255, 255}, (VEC2D){0, 0}, vertices, 7, &frag_shader);
	vlibc_sdl_flush_canvas(canvas);
}

int main(int argc, char *argv[]) {
	frag_shader = vlibc_create_fragment_shader(frag_shader_f);

	canvas = vlibc_sdl_alloc_canvas((VEC2D){WIDTH, HEIGHT});

	vlibc_sdl_create_window("test", WIDTH, HEIGHT);
	vlibc_sdl_start(display);
}