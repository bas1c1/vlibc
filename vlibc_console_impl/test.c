#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

#define WIDTH 40
#define HEIGHT 30

vlibc_uint32_t frag_shader_f(vlibc_fragment_shader_t* this, vlibc_vertex* vertices, int num_of_vertices, vlibc_vec2d frag_pos, vlibc_rgba frag_color) {
	return vlibc_rgba_to_hex(frag_color);
}

int main(int argc, char *argv[]) {
	vlibc_fragment_shader_t frag_shader = vlibc_create_fragment_shader(frag_shader_f, vlibc_nullptr, 0);

	vlibc_canvas canvas = vlibc_console_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});

	vlibc_fill(&canvas, VLIBC_RGBA_NULL, vlibc_nullptr);

	vlibc_vertex v6, v5, v4, v3, v2, v1, v0;
	v0.pos = (vlibc_vec2d){0, 0};
	v0.col = (vlibc_rgba){255, 0, 0, 255};

	v1.pos = (vlibc_vec2d){19, 0};
	v1.col = (vlibc_rgba){0, 255, 0, 255};

	v2.pos = (vlibc_vec2d){0, 19};
	v2.col = (vlibc_rgba){0, 0, 255, 255};

	v3.pos = (vlibc_vec2d){19, 19};
	v3.col = (vlibc_rgba){255, 255, 0, 255};

	v4.pos = (vlibc_vec2d){29, 29};
	v4.col = (vlibc_rgba){255, 255, 0, 255};

	v5.pos = (vlibc_vec2d){29, 19};
	v5.col = (vlibc_rgba){255, 0, 255, 255};

	v6.pos = (vlibc_vec2d){39, 0};
	v6.col = (vlibc_rgba){255, 255, 255, 255};

	vlibc_vertex vertices[7] = {v0, v1, v2, v3, v4, v5, v6};

	vlibc_filled_figure(&canvas, (vlibc_rgba){255, 255, 255, 255}, (vlibc_vec2d){0, 0}, vertices, 7, &frag_shader);

	vlibc_console_flush_canvas(canvas);
}