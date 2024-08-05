#ifndef __VLIBC__
#define __VLIBC__

typedef unsigned char vlibc_uint8_t;
typedef unsigned short vlibc_uint16_t;
typedef unsigned int vlibc_uint32_t;
typedef unsigned long int vlibc_uint64_t;
typedef long unsigned int vlibc_size_t;

#ifndef bool
typedef int bool;
enum { false, true };
#endif

#define VLIBCDEF static const

#define VLIBC_MIN(a,b) (((a)<(b))?(a):(b))
#define VLIBC_MAX(a,b) (((a)>(b))?(a):(b))

#define VLIBC_SIGN(T, a) ((T)(a > 0) - (T)(a < 0))
#define VLIBC_ABS(T, a) (VLIBC_SIGN(T, a)*a)

#define vlibc_nullptr ((void*)0)

#ifndef NULL
#define NULL '\0'
#endif

#define VLIBC_PI 3.141592653589793
#define VLIBC_HALF_PI 1.570796326794897
#define VLIBC_DOUBLE_PI 6.283185307179586
#define VLIBC_SIN_CURVE_A 0.0415896
#define VLIBC_SIN_CURVE_B 0.00129810625032

typedef struct {
	float x, y;
} vlibc_vec2d;

typedef struct {
	float x, y, z;
} vlibc_vec3d;

typedef struct {
	vlibc_uint32_t *pixels;
	vlibc_vec2d size;
} vlibc_canvas;

typedef struct {
	vlibc_uint8_t r, g, b, a;
} vlibc_rgba;

typedef struct {
	vlibc_vec2d pos;
	vlibc_rgba col;
} vlibc_vertex;

typedef struct vlibc_shader_data {
	float *data;
	vlibc_size_t size;
} vlibc_shader_data_t;

typedef struct vlibc_fragment_shader{
	vlibc_uint32_t (*func)(vlibc_vec2d frag_pos, vlibc_rgba frag_color, vlibc_shader_data_t data);
} vlibc_fragment_shader_t;

#define __vlibc_fast_put_pixel(vlibcc, color, pos) if (vlibc_in_bounds(vlibcc, pos) == true) { vlibcc->pixels[(int)(pos.y*vlibcc->size.x + pos.x)] = vlibc_rgba_to_hex(color); }

#define VLIBC_VEC2D_NULL ((vlibc_vec2d){0, 0})
#define VLIBC_VEC3D_NULL ((vlibc_vec3d){0, 0})
#define VLIBC_RGBA_NULL ((vlibc_rgba){0, 0})
#define VLIBC_VERTEX_NULL ((vlibc_vertex){VLIBC_VEC2D_NULL, VLIBC_RGBA_NULL})
#define VLIBC_CANVAS_NULL ((vlibc_canvas){vlibc_nullptr, VLIBC_VEC2D_NULL})
#define VLIBC_SHADER_DATA_NULL ((vlibc_shader_data_t){vlibc_nullptr, 0})

/*math functions*/
VLIBCDEF int vlibc_swap(int *f, int *s);
VLIBCDEF float vlibc_swap_float(float *f, float *s);
VLIBCDEF float vlibc_cross_product(vlibc_vec2d p1, vlibc_vec2d p2);
VLIBCDEF float vlibc_edge(vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p);
VLIBCDEF float vlibc_lerp(float a, float b, float t);
VLIBCDEF float vlibc_fract(float f);
VLIBCDEF float vlibc_clamp(float x, float a, float b);
VLIBCDEF float vlibc_saturate(float x);
VLIBCDEF float vlibc_smoothstep(float a, float b, float x);
VLIBCDEF int vlibc_step(float x, float num);
VLIBCDEF double vlibc_pow(double a, double b);
VLIBCDEF double vlibc_fact(double x);
VLIBCDEF double vlibc_sin(double x);
VLIBCDEF double vlibc_cos(double x);
VLIBCDEF float vlibc_dot(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF float vlibc_dot3(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec2d vlibc_normalize(vlibc_vec2d v);
VLIBCDEF vlibc_vec3d vlibc_normalize3(vlibc_vec3d v);
VLIBCDEF float vlibc_rsqrt(float x);
VLIBCDEF float vlibc_sqrt(float x);
VLIBCDEF float vlibc_length(vlibc_vec2d p);
VLIBCDEF float vlibc_length3(vlibc_vec3d p);
VLIBCDEF bool vlibc_in_bounds(vlibc_canvas *vlibcc, vlibc_vec2d p);

VLIBCDEF vlibc_uint32_t vlibc_rgba_to_hex(vlibc_rgba c);
VLIBCDEF vlibc_rgba vlibc_hex_to_rgba(vlibc_uint32_t c);

/*shader functions*/
VLIBCDEF vlibc_shader_data_t vlibc_create_shader_data(float *shader_data, vlibc_size_t shader_data_size);
VLIBCDEF vlibc_fragment_shader_t vlibc_create_fragment_shader(vlibc_uint32_t (*func)(vlibc_vec2d, vlibc_rgba, vlibc_shader_data_t));
VLIBCDEF vlibc_vec2d vlibc_calc_uv(vlibc_vec2d frag_pos, vlibc_vec2d resolution);
VLIBCDEF int vlibc_shader_data_parse_int(float *shader_data, int index);
VLIBCDEF vlibc_vec2d vlibc_shader_data_parse_vec2d(float *shader_data, int index);
VLIBCDEF vlibc_vec3d vlibc_shader_data_parse_vec3d(float *shader_data, int index);
VLIBCDEF vlibc_rgba vlibc_shader_data_parse_rgba(float *shader_data, int index);
VLIBCDEF vlibc_vertex vlibc_shader_data_parse_vertex(float *shader_data, int index);

/*gets average of red, green, blue and alpha and multiplies it by weight*/
VLIBCDEF vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2);
/*puts a pixel on position*/
VLIBCDEF void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos);
/*gets a pixel on position*/
VLIBCDEF vlibc_uint32_t vlibc_get_pixel(vlibc_canvas *vlibcc, vlibc_vec2d pos, int inversion);
/*fills entire canvas with one color*/
VLIBCDEF void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates rect without filling it*/
VLIBCDEF void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos1, vlibc_vec2d pos2, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates filled rect*/
VLIBCDEF void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d position, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates row*/
VLIBCDEF void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int width, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates column*/
VLIBCDEF void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int height, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates line*/
VLIBCDEF void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d start, vlibc_vec2d end, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates circle*/
VLIBCDEF void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates filled circle*/
VLIBCDEF void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates ellipse*/
VLIBCDEF void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates filled ellipse*/
VLIBCDEF void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates triangle*/
VLIBCDEF void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p3, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates filled triangle*/
VLIBCDEF void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);
/*creates figure with filled triangles*/
VLIBCDEF void vlibc_filled_figure(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, int num_of_vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data);

#endif

#ifdef __VLIBC_IMPL__

int vlibc_swap(int *f, int *s) {
	if (f == vlibc_nullptr && s == vlibc_nullptr) return -1;
	int t = 0;
	t = *f;
	*f = *s;
	*s = t;
	return t;
}

float vlibc_swap_float(float *f, float *s) {
	if (f == vlibc_nullptr && s == vlibc_nullptr) return -1;
	float t = 0;
	t = *f;
	*f = *s;
	*s = t;
	return t;
}

float vlibc_cross_product(vlibc_vec2d p1, vlibc_vec2d p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

vlibc_uint32_t vlibc_rgba_to_hex(vlibc_rgba c) {
	return (vlibc_uint32_t)( c.r&0xFF | (c.g&0xFF) << 8 | (c.b&0xFF) << 16 | (c.a&0xFF) << 24 );
}

vlibc_rgba vlibc_hex_to_rgba(vlibc_uint32_t c) {
	return *(vlibc_rgba*)&c;
}

float vlibc_lerp(float a, float b, float t) {
	return a + (t * (b - a));
}

float vlibc_fract(float f) {
	return f-(long)f;
}

float vlibc_clamp(float x, float a, float b) {
	return VLIBC_MAX(a, VLIBC_MIN(b, x));
}

float vlibc_saturate(float x) {
	return VLIBC_MAX(0, VLIBC_MIN(1, x));
}

float vlibc_smoothstep(float a, float b, float x) {
	float t = vlibc_saturate((x - a)/(b - a));
    return t*t*(3.0 - (2.0*t));
}

int vlibc_step(float x, float num) {
	return x > num ? 0 : 1;
}

double vlibc_pow(double a, double b) {
    double c = 1;
    for (int i=0; i<b; i++)
        c *= a;
    return c;
}

double vlibc_fact(double x) {
    double ret = 1;
    for (int i=1; i<=x; i++) 
        ret *= i;
    return ret;
}

/*i know this is super weird but it very fast*/
double vlibc_sin(double x) {
    x *= 0.63661977236758134308;
	int sign = x < 0.0;
	x = sign ? -x : x;
	int xf = (int)x;
	x -= xf;
	if ((xf & 1) == 1)
		x = 1 - x;
	int per = (xf >> 1) & 1;
	double y;
	if (x <= 0.5)
	{
		double xx = x * x;
		y = x * (1.5707963267948965822 + xx * (-0.6459640975062407217 +
			xx * (0.07969262624592800593 + xx * (-0.0046817541307639977752 +
			xx * (0.00016044114022967599853 + xx * (-3.5986097146969802712e-6 +
			5.629793865626169033e-8 * xx))))));
	}
	else
	{
		x = 1.0 - x;
		double xx = x * x;
		y = 1.0 - xx * (1.2337005501361513498 + xx * (-0.25366950789986513871 +
			xx * (0.020863480734953519901 + xx * (-0.0009192599500952791151 +
			xx * (0.000025200135454917479526 - 4.6552987291490935821e-7 * xx)))));
	}
	return sign ^ per ? -y : y;
}

double vlibc_cos(double x) {
	if (x < 0) {
        int q = -x / VLIBC_DOUBLE_PI;
        q += 1;
        double y = q * VLIBC_DOUBLE_PI;
        x = -(x - y);
    }
    if (x >= VLIBC_DOUBLE_PI) {
        int q = x / VLIBC_DOUBLE_PI;
        double y = q * VLIBC_DOUBLE_PI;
        x = x - y;
    }
    int s = 1;
    if (x >= VLIBC_PI) {
        s = -1;
        x -= VLIBC_PI;
    }
    if (x > VLIBC_HALF_PI) {
        x = VLIBC_PI - x;
        s = -s;
    }
    double z = x * x;
    double r = z * (z * (VLIBC_SIN_CURVE_A - VLIBC_SIN_CURVE_B * z) - 0.5) + 1.0;
    if (r > 1.0) r = r - 2.0;
    if (s > 0) return r;
    else return -r;
}

float vlibc_dot(vlibc_vec2d a, vlibc_vec2d b) {
	return a.x*b.x + a.y*b.y;
}

float vlibc_dot3(vlibc_vec3d a, vlibc_vec3d b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vlibc_vec2d vlibc_normalize(vlibc_vec2d v) {
	return (vlibc_vec2d) {
		.x = vlibc_rsqrt(vlibc_dot(v,v)) * v.x,
		.y = vlibc_rsqrt(vlibc_dot(v,v)) * v.y
	};
}

vlibc_vec3d vlibc_normalize3(vlibc_vec3d v) {
	return (vlibc_vec3d) {
		.x = vlibc_rsqrt(vlibc_dot3(v,v)) * v.x,
		.y = vlibc_rsqrt(vlibc_dot3(v,v)) * v.y,
		.z = vlibc_rsqrt(vlibc_dot3(v,v)) * v.z
	};
}

/*the legendary quake float Q_rsqrt( float number )*/
float vlibc_rsqrt(float x) {
	long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = x * 0.5F;
    y  = x;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

float vlibc_sqrt(float x) {
    return 1/vlibc_rsqrt(x);
}

float vlibc_length(vlibc_vec2d p) {
	return vlibc_sqrt(p.x*p.x + p.y*p.y);
}

float vlibc_length3(vlibc_vec3d p) {
	return vlibc_sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

bool vlibc_in_bounds(vlibc_canvas *vlibcc, vlibc_vec2d p) {
	if (p.x > vlibcc->size.x || p.y > vlibcc->size.y || p.x < 0 || p.y < 0) return false;
	return true;
}

float vlibc_edge(vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p) {
	vlibc_vec2d a = p;
	vlibc_vec2d b = p2;
	a.x -= p1.x;
	a.y -= p1.y;
	b.x -= p1.x;
	b.y -= p1.y;
	return a.x * b.y - a.y * b.x;
}

vlibc_fragment_shader_t vlibc_create_fragment_shader(vlibc_uint32_t (*func)(vlibc_vec2d, vlibc_rgba, vlibc_shader_data_t)) {
	return (vlibc_fragment_shader_t) {
		.func = func
	};
}

vlibc_shader_data_t vlibc_create_shader_data(float *shader_data, vlibc_size_t shader_data_size) {
	return (vlibc_shader_data_t) {
		shader_data,
		shader_data_size
	};
}

vlibc_vec2d vlibc_calc_uv(vlibc_vec2d frag_pos, vlibc_vec2d resolution) {
	vlibc_vec2d uv = (vlibc_vec2d) {
		.x = frag_pos.x/resolution.x * 2,
		.y = frag_pos.y/resolution.y * 2
	};
	uv.x -= 1;
	uv.y -= 1;
	uv.x *= resolution.x/resolution.y;
	return uv;
}

int vlibc_shader_data_parse_int(float *shader_data, int index) {
	if (shader_data == NULL) return -1;
	float x = *(shader_data+index);
	return 
		x >= 0
			?(int)(x + 0.5)
			:(int)(x - 0.5);
}

vlibc_vec2d vlibc_shader_data_parse_vec2d(float *shader_data, int index) {
	if (shader_data == NULL) return VLIBC_VEC2D_NULL;
	return (vlibc_vec2d) {
		.x = *(shader_data+index),
		.y = *(shader_data+index+1),
	};
}

vlibc_vec3d vlibc_shader_data_parse_vec3d(float *shader_data, int index) {
	if (shader_data == NULL) return VLIBC_VEC3D_NULL;
	return (vlibc_vec3d) {
		.x = *(shader_data+index),
		.y = *(shader_data+index+1),
		.z = *(shader_data+index+2),
	};
}

vlibc_vertex vlibc_shader_data_parse_vertex(float *shader_data, int index) {
	vlibc_vec2d p = (vlibc_vec2d){shader_data[index], shader_data[index+1]};
	vlibc_rgba c = (vlibc_rgba){shader_data[index+2], shader_data[index+3], shader_data[index+4], shader_data[index+5]};
	return (vlibc_vertex) {
		p, c
	};
}

vlibc_rgba vlibc_shader_data_parse_rgba(float *shader_data, int index) {
	if (shader_data == NULL) return VLIBC_RGBA_NULL;
	return (vlibc_rgba) {
		.r = *(shader_data+index),
		.g = *(shader_data+index+1),
		.b = *(shader_data+index+2),
		.a = *(shader_data+index+3),
	};
}

vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2) {
	vlibc_rgba output = (vlibc_rgba) {0, 0, 0, 0};
	output.r = 0.5 * c1.r + 0.5 * c2.r;
	output.g = 0.5 * c1.g + 0.5 * c2.g;
	output.b = 0.5 * c1.b + 0.5 * c2.b;
	output.a = 0.5 * c1.a + 0.5 * c2.a;
	return output;
}

void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos) {
	if (vlibcc == vlibc_nullptr) return;
	if (vlibc_in_bounds(vlibcc, pos) == false) return;
	vlibcc->pixels[(int)(pos.x*vlibcc->size.x + pos.y)] = vlibc_rgba_to_hex(color);
}

vlibc_uint32_t vlibc_get_pixel(vlibc_canvas *vlibcc, vlibc_vec2d pos, int inversion) {
	if (vlibcc == vlibc_nullptr) return -1;
	if (vlibc_in_bounds(vlibcc, pos) == false) return -1;
	if (inversion == 1)
		return vlibcc->pixels[(int)(pos.x*vlibcc->size.x + pos.y)];
	return vlibcc->pixels[(int)(pos.y*vlibcc->size.x + pos.x)];
}

void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_uint32_t conv_c = vlibc_rgba_to_hex(color);
	if (shader) {
		for (vlibc_size_t x = 0; x < vlibcc->size.x; x++) {
			for (vlibc_size_t y = 0; y < vlibcc->size.y; y++) {
				vlibc_vec2d p = (vlibc_vec2d){x, y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
		}
	} else {
		vlibc_size_t size = vlibcc->size.x * vlibcc->size.y;
		for (vlibc_size_t i = 0; i < size; i++) {
			vlibcc->pixels[i] = conv_c;
		}
	}
}

void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos1, vlibc_vec2d pos2, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_uint32_t conv_c = vlibc_rgba_to_hex(color);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos1.y}, (vlibc_vec2d){pos2.x, pos1.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos1.y}, (vlibc_vec2d){pos1.x, pos2.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos2.y}, (vlibc_vec2d){pos2.x, pos2.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos2.x, pos1.y}, (vlibc_vec2d){pos2.x, pos2.y}, shader, shader_data);
}

void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d position, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_filled_triangle(vlibcc, color, position, vertices, shader, shader_data);
	vlibc_filled_triangle(vlibcc, color, position, vertices + 1, shader, shader_data);
}

void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int width, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_uint32_t conv_c = vlibc_rgba_to_hex(color);
	if (shader) {
		for (int i = 0; i < width; i++) {
			vlibc_vec2d p = {pos.x+i, pos.y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		}
	} else {
		for (int i = 0; i < width; i++) {
			vlibc_vec2d p = {pos.x+i, pos.y};
			__vlibc_fast_put_pixel(vlibcc, color, p);
		}
	}
}

void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int height, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_uint32_t conv_c = vlibc_rgba_to_hex(color);
	
	if (shader) {
		for (int i = 0; i < height; i++) {
			vlibc_vec2d p = {pos.x, pos.y+i};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		}
	} else {
		for (int i = 0; i < height; i++) {
			vlibc_vec2d p = {pos.x, pos.y+i};
			__vlibc_fast_put_pixel(vlibcc, color, p);
		}
	}
}

void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d start, vlibc_vec2d end, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	int dx = end.x - start.x;
	int dy = end.y - start.y;

	if (dx == 0 && dy == 0) {
		if (shader) {
			color = vlibc_hex_to_rgba(shader->func(start, color, shader_data));
		}
		__vlibc_fast_put_pixel(vlibcc, color, start);
		return;
	}

	if (VLIBC_ABS(int, dx) > VLIBC_ABS(int, dy)) {
		if (start.x > end.x) {
			vlibc_swap_float(&start.x, &end.x);
			vlibc_swap_float(&start.y, &end.y);
		}
		if (shader) {
			for (int x = start.x; x <= end.x; ++x) {
				vlibc_vec2d p = {x, dy*(x - start.x)/dx + start.y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
		} else {
			for (int x = start.x; x <= end.x; ++x) {
				vlibc_vec2d p = {x, dy*(x - start.x)/dx + start.y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
		}
	} else {
		if (start.y > end.y) {
			vlibc_swap_float(&start.x, &end.x);
			vlibc_swap_float(&start.y, &end.y);
		}
		if (shader) {
			for (int y = start.y; y <= end.y; ++y) {
				vlibc_vec2d p = {dx*(y - start.y)/dy + start.x, y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
		} else {
			for (int y = start.y; y <= end.y; ++y) {
				vlibc_vec2d p = {dx*(y - start.y)/dy + start.x, y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
		}
	}
}

void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	pos.x += r;
	pos.y += r;
	int x = 0, y = r;
	int d = 3 - 2 * r;

	if (shader) {
		vlibc_vec2d p = {pos.x+x, pos.y+y};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x-x, pos.y+y};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x+x, pos.y-y};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x-x, pos.y-y};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x+y, pos.y+x};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x-y, pos.y+x};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x+y, pos.y-x};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		p = (vlibc_vec2d){pos.x-y, pos.y-x};
		__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
	}

	vlibc_vec2d p = {pos.x+x, pos.y+y};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x-x, pos.y+y};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x+x, pos.y-y};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x-x, pos.y-y};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x+y, pos.y+x};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x-y, pos.y+x};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x+y, pos.y-x};
	__vlibc_fast_put_pixel(vlibcc, color, p);
	p = (vlibc_vec2d){pos.x-y, pos.y-x};
	__vlibc_fast_put_pixel(vlibcc, color, p);

	while (y >= x)
	{
		x++;

		if (d > 0)
		{
			y--; 
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		if (shader) {
			p = (vlibc_vec2d){pos.x+x, pos.y+y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x-x, pos.y+y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x+x, pos.y-y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x-x, pos.y-y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x+y, pos.y+x};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x-y, pos.y+x};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x+y, pos.y-x};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			p = (vlibc_vec2d){pos.x-y, pos.y-x};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
		}

		p = (vlibc_vec2d){pos.x+x, pos.y+y};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x-x, pos.y+y};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x+x, pos.y-y};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x-x, pos.y-y};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x+y, pos.y+x};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x-y, pos.y+x};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x+y, pos.y-x};
		__vlibc_fast_put_pixel(vlibcc, color, p);
		p = (vlibc_vec2d){pos.x-y, pos.y-x};
		__vlibc_fast_put_pixel(vlibcc, color, p);
	}
}

void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	pos.x += r;
	pos.y += r;
	int x = r;
	int y = 0;
	int xChange = 1 - (r << 1);
	int yChange = 0;
	int radiusError = 0;

	vlibc_vec2d p;

	while (x >= y)
	{
		if (shader) {
			for (int i = pos.x - x; i <= pos.x + x; i++) {
				p = (vlibc_vec2d){i, pos.y + y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
				p = (vlibc_vec2d){i, pos.y - y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
			for (int i = pos.x - y; i <= pos.x + y; i++) {
				p = (vlibc_vec2d){i, pos.y + x};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
				p = (vlibc_vec2d){i, pos.y - x};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
		} else {
			for (int i = pos.x - x; i <= pos.x + x; i++) {
				p = (vlibc_vec2d){i, pos.y + y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
				p = (vlibc_vec2d){i, pos.y - y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
			for (int i = pos.x - y; i <= pos.x + y; i++) {
				p = (vlibc_vec2d){i, pos.y + x};
				__vlibc_fast_put_pixel(vlibcc, color, p);
				p = (vlibc_vec2d){i, pos.y - x};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

#define incx() x++, dxt += d2xt, t += dxt
#define incy() y--, dyt += d2yt, t += dyt

void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	pos.x += rx;
	pos.y += ry;
	int x = 0, y = ry;
	long a2 = (long)rx*rx, b2 = (long)ry*ry;
	long crit1 = -(a2/4 + rx%2 + b2);
	long crit2 = -(b2/4 + ry%2 + a2);
	long crit3 = -(b2/4 + ry%2);
	long t = -a2*y;
	long dxt = 2*b2*x, dyt = -2*a2*y;
	long d2xt = 2*b2, d2yt = 2*a2;

	vlibc_vec2d p = {0, 0};

	if (shader) {
		while (y>=0 && x<=rx) {
			p = (vlibc_vec2d){pos.x+x, pos.y+y};
			__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			if (x!=0 || y!=0) {
				p = (vlibc_vec2d){pos.x-x, pos.y-y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
			if (x!=0 && y!=0) {
				p = (vlibc_vec2d){pos.x+x, pos.y-y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
				p = (vlibc_vec2d){pos.x-x, pos.y+y};
				__vlibc_fast_put_pixel(vlibcc, vlibc_hex_to_rgba(shader->func(p, color, shader_data)), p);
			}
			if (t + b2*x <= crit1 || t + a2*y <= crit3)
				incx();
			else if (t - a2*y > crit2)
				incy();
			else {
				incx();
				incy();
			}
		}
	} else {
		while (y>=0 && x<=rx) {
			p = (vlibc_vec2d){pos.x+x, pos.y+y};
			__vlibc_fast_put_pixel(vlibcc, color, p);
			if (x!=0 || y!=0) {
				p = (vlibc_vec2d){pos.x-x, pos.y-y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
			if (x!=0 && y!=0) {
				p = (vlibc_vec2d){pos.x+x, pos.y-y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
				p = (vlibc_vec2d){pos.x-x, pos.y+y};
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
			if (t + b2*x <= crit1 || t + a2*y <= crit3)
				incx();
			else if (t - a2*y > crit2)
				incy();
			else {
				incx();
				incy();
			}
		}
	}
}

void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	pos.x += rx;
	pos.y += ry;
	int x = 0, y = ry;
	unsigned int width = 1;
	long a2 = (long)rx*rx, b2 = (long)ry*ry;
	long crit1 = -(a2/4 + rx%2 + b2);
	long crit2 = -(b2/4 + ry%2 + a2);
	long crit3 = -(b2/4 + ry%2);
	long t = -a2*y;
	long dxt = 2*b2*x, dyt = -2*a2*y;
	long d2xt = 2*b2, d2yt = 2*a2;

	while (y>=0 && x<=rx) {
		if (t + b2*x <= crit1 || t + a2*y <= crit3) {
			incx();
			width += 2;
		}
		else if (t - a2*y > crit2) {
			vlibc_row(vlibcc, color, (vlibc_vec2d){pos.x-x, pos.y-y}, width, shader, shader_data);
			if (y!=0)
				vlibc_row(vlibcc, color, (vlibc_vec2d){pos.x-x, pos.y+y}, width, shader, shader_data);
			incy();
		}
		else {
			vlibc_row(vlibcc, color, (vlibc_vec2d){pos.x-x, pos.y-y}, width, shader, shader_data);
			if (y!=0)
				vlibc_row(vlibcc, color, (vlibc_vec2d){pos.x-x, pos.y+y}, width, shader, shader_data);
			incx();
			incy();
			width += 2;
		}
	}
	if (ry == 0)
		vlibc_row(vlibcc, color, (vlibc_vec2d){pos.x-rx, pos.y}, 2*rx+1, shader, shader_data);
}

#undef incx
#undef incy

void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p3, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	p1.x += pos.x;
	p1.y += pos.y;

	p2.x += pos.x;
	p2.y += pos.y;

	p3.x += pos.x;
	p3.y += pos.y;

	vlibc_line(vlibcc, color, p1, p2, shader, shader_data);
	vlibc_line(vlibcc, color, p2, p3, shader, shader_data);
	vlibc_line(vlibcc, color, p3, p1, shader, shader_data);
}

void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_vertex p1 = vertices[0];
	vlibc_vertex p2 = vertices[1];
	vlibc_vertex p3 = vertices[2];

	p1.pos.x += pos.x;
	p1.pos.y += pos.y;

	p2.pos.x += pos.x;
	p2.pos.y += pos.y;

	p3.pos.x += pos.x;
	p3.pos.y += pos.y;

	float area = vlibc_edge(p3.pos, p2.pos, p1.pos);

	vlibc_rgba ncolor;

	int maxX = VLIBC_MAX(p1.pos.x, VLIBC_MAX(p2.pos.x, p3.pos.x));
	int minX = VLIBC_MIN(p1.pos.x, VLIBC_MIN(p2.pos.x, p3.pos.x));
	int maxY = VLIBC_MAX(p1.pos.y, VLIBC_MAX(p2.pos.y, p3.pos.y));
	int minY = VLIBC_MIN(p1.pos.y, VLIBC_MIN(p2.pos.y, p3.pos.y));

	vlibc_vec2d vs1 = (vlibc_vec2d){p2.pos.x - p1.pos.x, p2.pos.y - p1.pos.y};
	vlibc_vec2d vs2 = (vlibc_vec2d){p3.pos.x - p1.pos.x, p3.pos.y - p1.pos.y};

	vlibc_vertex nvertices[3] = {p1, p2, p3};

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			vlibc_vec2d q = (vlibc_vec2d){x - p1.pos.x, y - p1.pos.y};

			float s = (float)vlibc_cross_product(q, vs2) / vlibc_cross_product(vs1, vs2);
			float t = (float)vlibc_cross_product(vs1, q) / vlibc_cross_product(vs1, vs2);

			vlibc_vec2d p = {x, y};

			if ( (s >= 0) && (t >= 0) && (s + t <= 1)) {
				if (shader) {
					float e0 = vlibc_edge(p3.pos, p2.pos, p);
					float e1 = vlibc_edge(p1.pos, p3.pos, p);
					float e2 = vlibc_edge(p2.pos, p1.pos, p);

					float w0 = e0 / area;
					float w1 = e1 / area;
					float w2 = e2 / area;

					float r = w0 * p1.col.r + w1 * p2.col.r + w2 * p3.col.r;
					float g = w0 * p1.col.g + w1 * p2.col.g + w2 * p3.col.g;
					float b = w0 * p1.col.b + w1 * p2.col.b + w2 * p3.col.b;

					ncolor = (vlibc_rgba) {
						.r = r,
						.g = g,
						.b = b,
						.a = color.a
					};

					color = vlibc_hex_to_rgba(shader->func(p, ncolor, shader_data));
				}
				__vlibc_fast_put_pixel(vlibcc, color, p);
			}
		}
	}
}

void vlibc_filled_figure(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, int num_of_vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	for (vlibc_size_t i = 0; i+2 < num_of_vertices; i++) {
		vlibc_filled_triangle(vlibcc, color, pos, vertices+i, shader, shader_data);
	}
}

#endif