#define __VLIBC_SDL_IMPL__
#define SDL_MAIN_HANDLED
#include "vlibc_sdl.h"

#define WIDTH 400
#define HEIGHT 400

vlibc_uint32_t frag_shader_f(vlibc_fragment_shader_t* this, vlibc_vertex* vertices, int num_of_vertices, vlibc_vec2d frag_pos, vlibc_rgba frag_color) {
	vlibc_rgba color = vlibc_mix_colors(frag_color, vlibc_shader_data_parse_rgba(this->shader_data, 8));

	return vlibc_rgba_to_hex(color);
}

vlibc_fragment_shader_t frag_shader;
vlibc_canvas canvas;

void display() {
	vlibc_vertex v6, v5, v4, v3, v2, v1, v0;
	v0.pos = (vlibc_vec2d){0, 0};
	v0.col = (vlibc_rgba){255, 0, 0, 255};

	v1.pos = (vlibc_vec2d){190, 0};
	v1.col = (vlibc_rgba){0, 255, 0, 255};

	v2.pos = (vlibc_vec2d){0, 190};
	v2.col = (vlibc_rgba){0, 0, 255, 255};

	v3.pos = (vlibc_vec2d){190, 190};
	v3.col = (vlibc_rgba){255, 255, 0, 255};

	v4.pos = (vlibc_vec2d){290, 290};
	v4.col = (vlibc_rgba){255, 255, 0, 255};

	v5.pos = (vlibc_vec2d){290, 190};
	v5.col = (vlibc_rgba){255, 0, 255, 255};

	v6.pos = (vlibc_vec2d){390, 0};
	v6.col = (vlibc_rgba){255, 255, 255, 255};

	vlibc_vertex vertices[7] = {v0, v1, v2, v3, v4, v5, v6};

	vlibc_filled_figure(&canvas, (vlibc_rgba){255, 255, 255, 255}, (vlibc_vec2d){0, 0}, vertices, 7, &frag_shader);

	vlibc_sdl_flush_canvas(canvas);
}

int main(int argc, char *argv[]) {
	float data[] = {
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	frag_shader = vlibc_create_fragment_shader(frag_shader_f, data, 12);

	canvas = vlibc_sdl_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});

	vlibc_sdl_create_window("test", WIDTH, HEIGHT);
	vlibc_sdl_start(display);

	return 0;
}
