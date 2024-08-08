#define __VLIBC_CONSOLE_IMPL__
#include "vlibc_console.h"

#define WIDTH 40
#define HEIGHT 30

vlibc_uint32_t frag_shader_f(vlibc_vec2d frag_pos, vlibc_rgba frag_color, vlibc_shader_data_t *data) {
	return vlibc_rgba_to_hex(vlibc_f_rgba_to_rgba(data->passthrough_data[0]));
}

int main(int argc, char *argv[]) {
	vlibc_fragment_shader_t frag_shader = vlibc_create_fragment_shader(frag_shader_f);

	vlibc_canvas canvas = vlibc_console_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});

	vlibc_fill(&canvas, VLIBC_RGBA_NULL, vlibc_nullptr, vlibc_nullptr);

	vlibc_f_rgba attribute1 = (vlibc_f_rgba) {
		255, 0, 0, 255
	};

	vlibc_f_rgba attribute2 = (vlibc_f_rgba) {
		0, 255, 0, 255
	};

	vlibc_f_rgba attribute3 = (vlibc_f_rgba) {
		0, 0, 255, 255
	};

	vlibc_vertex vertices[3] = {
		(vlibc_vertex) {(vlibc_vec2d) {0, 0}, &attribute1, 1},
		(vlibc_vertex) {(vlibc_vec2d) {WIDTH / 2, HEIGHT}, &attribute2, 1},
		(vlibc_vertex) {(vlibc_vec2d) {WIDTH, 0}, &attribute3, 1}
	};

	vlibc_f_rgba passthrough_data = {};
	vlibc_shader_data_t frag_shader_data = vlibc_create_shader_data(vlibc_nullptr, 0, &passthrough_data);

	vlibc_filled_triangle(&canvas, VLIBC_RGBA_NULL, VLIBC_VEC2D_NULL, vertices, &frag_shader, &frag_shader_data);

	vlibc_console_flush_canvas(&canvas);
}