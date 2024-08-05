#define __VLIBC_SDL_IMPL__
#define SDL_MAIN_HANDLED
#include "vlibc_sdl.h"

#define WIDTH 300
#define HEIGHT 300

vlibc_shader_data_t frag_shader_data;
vlibc_fragment_shader_t frag_shader;
vlibc_canvas canvas;

const int MAX_MARCHING_STEPS = 255;
const float MIN_DIST = 0.0;
const float MAX_DIST = 100.0;
const float PRECISION = 0.001;

float sdSphere(vlibc_vec3d p, float r ) {
	return vlibc_length3(p) - r;
}

float rayMarch(vlibc_vec3d ro, vlibc_vec3d rd, float start, float end) {
	float depth = start;

	for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
		vlibc_vec3d p; 
		p.x = ro.x + depth * rd.x;
		p.y = ro.y + depth * rd.y;
		p.z = ro.z + depth * rd.z;
		float d = sdSphere(p, 1);
		depth += d;
		if (d < PRECISION || depth > end) break;
	}

	return depth;
}

vlibc_vec3d calcNormal(vlibc_vec3d p) {
    vlibc_vec2d e = (vlibc_vec2d){1.0 * 0.0005, -1.0 * 0.0005};
    float r = 1;

    vlibc_vec3d xyy = {e.x, e.y, e.y};
    vlibc_vec3d yyx = {e.y, e.y, e.x};
    vlibc_vec3d yxy = {e.y, e.x, e.y};
    vlibc_vec3d xxx = {e.x, e.x, e.x};

    vlibc_vec3d sxyy = {e.x + p.x, e.y + p.y, e.y + p.z};
    vlibc_vec3d syyx = {e.y + p.x, e.y + p.y, e.x + p.z};
    vlibc_vec3d syxy = {e.y + p.x, e.x + p.y, e.y + p.z};
    vlibc_vec3d sxxx = {e.x + p.x, e.x + p.y, e.x + p.z};

    xyy.x *= sdSphere(sxyy, r); xyy.y *= sdSphere(sxyy, r); xyy.z *= sdSphere(sxyy, r);
    yyx.x *= sdSphere(syyx, r); yyx.y *= sdSphere(syyx, r); yyx.z *= sdSphere(syyx, r);
    yxy.x *= sdSphere(syxy, r); yxy.y *= sdSphere(syxy, r); yxy.z *= sdSphere(syxy, r);
    xxx.x *= sdSphere(sxxx, r); xxx.y *= sdSphere(sxxx, r); xxx.z *= sdSphere(sxxx, r);

    vlibc_vec3d f = VLIBC_VEC3D_NULL;
    f.x += xyy.x + yyx.x + yxy.x + xxx.x;
    f.y += xyy.y + yyx.y + yxy.y + xxx.y;
    f.z += xyy.z + yyx.z + yxy.z + xxx.z;

    return vlibc_normalize3(f);
}

vlibc_uint32_t frag_shader_f(vlibc_vec2d frag_pos, vlibc_rgba frag_color, vlibc_shader_data_t data) {
	vlibc_vec2d uv = vlibc_calc_uv(frag_pos, canvas.size);
	vlibc_vec3d final_col = VLIBC_VEC3D_NULL;

	vlibc_vec3d ro = (vlibc_vec3d){0, 0, 3};
	vlibc_vec3d rd = vlibc_normalize3((vlibc_vec3d){uv.x, uv.y, -1});

	float d = rayMarch(ro, rd, MIN_DIST, MAX_DIST);

	if (d > MAX_DIST) {
		final_col = (vlibc_vec3d){0.6*255, 0.6*255, 0.6*255};
	} else {
		vlibc_vec3d p; 
		p.x = ro.x + rd.x * d;
		p.y = ro.y + rd.y * d;
		p.z = ro.z + rd.z * d;
		vlibc_vec3d normal = calcNormal(p);
		vlibc_vec3d lightPosition = (vlibc_vec3d){2, -4, 7};
		vlibc_vec3d lightDirection = vlibc_normalize3((vlibc_vec3d){lightPosition.x - p.x, lightPosition.y - p.y, lightPosition.z - p.z});

		float dif = vlibc_clamp(vlibc_dot3(normal, lightDirection), 0.3, 1.);

		final_col.x = dif * 255;
		final_col.y = dif * 255 * 0.58;
		final_col.z = dif * 255 * 0.29;
	}

	return vlibc_rgba_to_hex((vlibc_rgba){final_col.x, final_col.y, final_col.z, 255});
}

void display() {
	vlibc_fill(&canvas, (vlibc_rgba){255, 255, 255, 255}, &frag_shader, frag_shader_data);

	vlibc_sdl_flush_canvas(&canvas);
}

int main(int argc, char *argv[]) {
	float data[] = {
		255, 255, 255, 255,
		0, 255, 0, 255,
		0, 0, 255, 255
	};

	frag_shader = vlibc_create_fragment_shader(frag_shader_f);
	frag_shader_data = vlibc_create_shader_data(data, 12);

	canvas = vlibc_sdl_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});

	vlibc_sdl_create_window("test", WIDTH, HEIGHT);
	vlibc_sdl_start(display);

	return 0;
}
