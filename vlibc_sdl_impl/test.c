#define __VLIBC_SDL_IMPL__
#define SDL_MAIN_HANDLED
#include "vlibc_sdl.h"

#define WIDTH 400
#define HEIGHT 400

vlibc_fragment_shader_t frag_shader;
vlibc_canvas canvas;

vlibc_uint32_t frag_shader_f(vlibc_fragment_shader_t* this, vlibc_vertex* vertices, int num_of_vertices, vlibc_vec2d frag_pos, vlibc_rgba frag_color) {
	//return vlibc_rgba_to_hex(frag_color);
	vlibc_vec2d uv = vlibc_calc_uv(frag_pos, canvas.size);

	float d = vlibc_length(uv);

	vlibc_rgba col = (vlibc_rgba){125, 223, 87, 255};

	d = vlibc_sin(d * 8 + __vlibc_sdl_time/5) / 8;
	d = VLIBC_ABS(float, d);

	d = 0.02 / d;

	col.r *= d;
	col.g *= d;
	col.b *= d;

	return vlibc_rgba_to_hex((vlibc_rgba){col.r, col.g, col.b, 255});
}

void display() {
	vlibc_fill(&canvas, (vlibc_rgba){255, 255, 255, 255}, &frag_shader);
	vlibc_sdl_flush_canvas(&canvas);
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
