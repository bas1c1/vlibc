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

#ifndef VLIBC_NULL
#define VLIBC_NULL '\0'
#endif

#define vlibc_nullptr ((void*)VLIBC_NULL)

#define VLIBC_PI 3.141592653589793
#define VLIBC_HALF_PI 1.570796326794897
#define VLIBC_DOUBLE_PI 6.283185307179586
#define VLIBC_SIN_CURVE_A 0.0415896
#define VLIBC_SIN_CURVE_B 0.00129810625032
#define VLIBC_RAD2DEG (180.f / VLIBC_PI)
#define VLIBC_DEG2RAD  (VLIBC_PI / 180.f)

typedef struct {
	float x, y;
} vlibc_vec2d;

typedef struct {
	float x, y, z;
} vlibc_vec3d;

typedef struct {
	float x, y, z, w;
} vlibc_vec4d;

typedef struct {
	vlibc_uint32_t *pixels;
	vlibc_vec2d size;
} vlibc_canvas;

typedef struct {
	vlibc_uint8_t r, g, b, a;
} vlibc_rgba;

typedef struct {
	float r, g, b, a;
} vlibc_f_rgba;

typedef struct {
	vlibc_vec2d pos;
	vlibc_f_rgba* col;
	int col_count;
} vlibc_vertex;

typedef union {
	float m[4][4];

	struct {
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
} vlibc_mat4_t;

typedef struct vlibc_shader_data {
	float *data;
	vlibc_f_rgba* passthrough_data;
	vlibc_size_t size;
} vlibc_shader_data_t;

typedef struct vlibc_fragment_shader{
	vlibc_uint32_t (*func)(vlibc_vec2d frag_pos, vlibc_rgba frag_color, vlibc_shader_data_t* data);
} vlibc_fragment_shader_t;

#define __vlibc_fast_put_pixel(vlibcc, color, pos) if (vlibc_in_bounds(vlibcc, pos) == true) { vlibcc->pixels[(int)(pos.y*vlibcc->size.x + pos.x)] = vlibc_rgba_to_hex(color); }

#define VLIBC_VEC2D_NULL ((vlibc_vec2d){0, 0})
#define VLIBC_VEC3D_NULL ((vlibc_vec3d){0, 0})
#define VLIBC_VEC4D_NULL ((vlibc_vec4d){0, 0})
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
VLIBCDEF float vlibc_linearize_depth(float d, float near, float far);
VLIBCDEF float vlibc_fract(float f);
VLIBCDEF float vlibc_clamp(float x, float a, float b);
VLIBCDEF float vlibc_saturate(float x);
VLIBCDEF float vlibc_smoothstep(float a, float b, float x);
VLIBCDEF int vlibc_step(float x, float num);
VLIBCDEF double vlibc_pow(double a, double b);
VLIBCDEF double vlibc_fact(double x);
VLIBCDEF double vlibc_sin(double x);
VLIBCDEF double vlibc_cos(double x);
VLIBCDEF double vlibc_tan(double x);
VLIBCDEF float vlibc_rsqrt(float x);
VLIBCDEF float vlibc_sqrt(float x);
VLIBCDEF bool vlibc_in_bounds(vlibc_canvas *vlibcc, vlibc_vec2d p);

/*vector functions*/
VLIBCDEF vlibc_vec3d vlibc_vec3d_cross(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec3d vlibc_vec3d_proj(vlibc_vec3d v, vlibc_vec3d onto);

VLIBCDEF float vlibc_vec2d_dot(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF float vlibc_vec3d_dot(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF float vlibc_vec4d_dot(vlibc_vec4d a, vlibc_vec4d b);

VLIBCDEF vlibc_vec2d vlibc_vec2d_normalize(vlibc_vec2d v);
VLIBCDEF vlibc_vec3d vlibc_vec3d_normalize(vlibc_vec3d v);
VLIBCDEF vlibc_vec4d vlibc_vec4d_normalize(vlibc_vec4d v);

VLIBCDEF float vlibc_vec2d_length(vlibc_vec2d p);
VLIBCDEF float vlibc_vec3d_length(vlibc_vec3d p);
VLIBCDEF float vlibc_vec4d_length(vlibc_vec4d p);

VLIBCDEF vlibc_vec2d vlibc_vec2d_reflect(vlibc_vec2d i, vlibc_vec2d n);
VLIBCDEF vlibc_vec3d vlibc_vec3d_reflect(vlibc_vec3d i, vlibc_vec3d n);
VLIBCDEF vlibc_vec4d vlibc_vec4d_reflect(vlibc_vec4d i, vlibc_vec4d n);

VLIBCDEF vlibc_vec2d vlibc_vec2d_negate(vlibc_vec2d x);
VLIBCDEF vlibc_vec3d vlibc_vec3d_negate(vlibc_vec3d x);
VLIBCDEF vlibc_vec4d vlibc_vec4d_negate(vlibc_vec4d x);

VLIBCDEF vlibc_vec2d vlibc_mul_vec2d(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF vlibc_vec2d vlibc_mul_vec2df(vlibc_vec2d a, float b);
VLIBCDEF vlibc_vec3d vlibc_mul_vec3d(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec3d vlibc_mul_vec3df(vlibc_vec3d a, float b);
VLIBCDEF vlibc_vec4d vlibc_mul_vec4d(vlibc_vec4d a, vlibc_vec4d b);
VLIBCDEF vlibc_vec4d vlibc_mul_vec4df(vlibc_vec4d a, float b);

VLIBCDEF vlibc_vec2d vlibc_add_vec2d(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF vlibc_vec2d vlibc_add_vec2df(vlibc_vec2d a, float b);
VLIBCDEF vlibc_vec3d vlibc_add_vec3d(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec3d vlibc_add_vec3df(vlibc_vec3d a, float b);
VLIBCDEF vlibc_vec4d vlibc_add_vec4d(vlibc_vec4d a, vlibc_vec4d b);
VLIBCDEF vlibc_vec4d vlibc_add_vec4df(vlibc_vec4d a, float b);

VLIBCDEF vlibc_vec2d vlibc_div_vec2d(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF vlibc_vec2d vlibc_div_vec2df(vlibc_vec2d a, float b);
VLIBCDEF vlibc_vec3d vlibc_div_vec3d(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec3d vlibc_div_vec3df(vlibc_vec3d a, float b);
VLIBCDEF vlibc_vec4d vlibc_div_vec4d(vlibc_vec4d a, vlibc_vec4d b);
VLIBCDEF vlibc_vec4d vlibc_div_vec4df(vlibc_vec4d a, float b);

VLIBCDEF vlibc_vec2d vlibc_sub_vec2d(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF vlibc_vec2d vlibc_sub_vec2df(vlibc_vec2d a, float b);
VLIBCDEF vlibc_vec3d vlibc_sub_vec3d(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF vlibc_vec3d vlibc_sub_vec3df(vlibc_vec3d a, float b);
VLIBCDEF vlibc_vec4d vlibc_sub_vec4d(vlibc_vec4d a, vlibc_vec4d b);
VLIBCDEF vlibc_vec4d vlibc_sub_vec4df(vlibc_vec4d a, float b);

VLIBCDEF vlibc_vec2d vlibc_div_fvec2d(float b, vlibc_vec2d a);
VLIBCDEF vlibc_vec3d vlibc_div_fvec3d(float b, vlibc_vec3d a);
VLIBCDEF vlibc_vec4d vlibc_div_fvec4d(float b, vlibc_vec4d a);

VLIBCDEF vlibc_vec2d vlibc_sub_fvec2d(float b, vlibc_vec2d a);
VLIBCDEF vlibc_vec3d vlibc_sub_fvec3d(float b, vlibc_vec3d a);
VLIBCDEF vlibc_vec4d vlibc_sub_fvec4d(float b, vlibc_vec4d a);

VLIBCDEF bool vlibc_vec2d_equal(vlibc_vec2d a, vlibc_vec2d b);
VLIBCDEF bool vlibc_vec3d_equal(vlibc_vec3d a, vlibc_vec3d b);
VLIBCDEF bool vlibc_vec4d_equal(vlibc_vec4d a, vlibc_vec4d b);
VLIBCDEF bool vlibc_rgba_equal(vlibc_rgba a, vlibc_rgba b);
VLIBCDEF bool vlibc_vertex_equal(vlibc_vertex a, vlibc_vertex b);

/*matrix functions*/
VLIBCDEF vlibc_mat4_t vlibc_mat4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33);
VLIBCDEF vlibc_mat4_t vlibc_mat4_identity();
VLIBCDEF vlibc_mat4_t vlibc_mat4_translation(vlibc_vec3d offset);
VLIBCDEF vlibc_mat4_t vlibc_mat4_scaling(vlibc_vec3d scale);
VLIBCDEF vlibc_mat4_t vlibc_mat4_rotation_x(float angle_in_rad);
VLIBCDEF vlibc_mat4_t vlibc_mat4_rotation_y(float angle_in_rad);
VLIBCDEF vlibc_mat4_t vlibc_mat4_rotation_z(float angle_in_rad);
VLIBCDEF vlibc_mat4_t vlibc_mat4_rotation(float angle_in_rad, vlibc_vec3d axis);
VLIBCDEF vlibc_mat4_t vlibc_mat4_ortho(float left, float right, float bottom, float top, float back, float front);
VLIBCDEF vlibc_mat4_t vlibc_mat4_perspective(float vertical_field_of_view_in_deg, float aspect_ratio, float near_view_distance, float far_view_distance);
VLIBCDEF vlibc_mat4_t vlibc_mat4_look_at(vlibc_vec3d from, vlibc_vec3d to, vlibc_vec3d up);
VLIBCDEF vlibc_mat4_t vlibc_mat4_transpose(vlibc_mat4_t matrix);
VLIBCDEF vlibc_mat4_t vlibc_mat4_mul(vlibc_mat4_t a, vlibc_mat4_t b);
VLIBCDEF vlibc_mat4_t vlibc_mat4_invert_affine(vlibc_mat4_t matrix);
VLIBCDEF vlibc_vec3d vlibc_mat4_mul_pos(vlibc_mat4_t matrix, vlibc_vec3d position);
VLIBCDEF vlibc_vec3d vlibc_mat4_mul_dir(vlibc_mat4_t matrix, vlibc_vec3d direction);

/*color convertion*/
VLIBCDEF vlibc_rgba vlibc_f_rgba_to_rgba(vlibc_f_rgba rgba);
VLIBCDEF vlibc_uint32_t vlibc_rgba_to_hex(vlibc_rgba c);
VLIBCDEF vlibc_rgba vlibc_hex_to_rgba(vlibc_uint32_t c);

/*shader functions*/
VLIBCDEF vlibc_shader_data_t vlibc_create_shader_data(float *shader_data, vlibc_size_t shader_data_size, vlibc_f_rgba *passthrough_data);
VLIBCDEF vlibc_fragment_shader_t vlibc_create_fragment_shader(vlibc_uint32_t (*func)(vlibc_vec2d, vlibc_rgba, vlibc_shader_data_t*));
VLIBCDEF vlibc_vec2d vlibc_calc_uv(vlibc_vec2d frag_pos, vlibc_vec2d resolution);
VLIBCDEF int vlibc_shader_data_parse_int(float *shader_data, int index);
VLIBCDEF vlibc_vec2d vlibc_shader_data_parse_vec2d(float *shader_data, int index);
VLIBCDEF vlibc_vec3d vlibc_shader_data_parse_vec3d(float *shader_data, int index);
VLIBCDEF vlibc_vec4d vlibc_shader_data_parse_vec4d(float *shader_data, int index);
VLIBCDEF vlibc_rgba vlibc_shader_data_parse_rgba(float *shader_data, int index);
VLIBCDEF vlibc_vertex vlibc_shader_data_parse_vertex(float *shader_data, int index);

/*gets average of red, green, blue and alpha and multiplies it by phase*/
VLIBCDEF vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2, float phase);
/*puts a pixel on position*/
VLIBCDEF void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos);
/*gets a pixel on position*/
VLIBCDEF vlibc_uint32_t vlibc_get_pixel(vlibc_canvas *vlibcc, vlibc_vec2d pos, int inversion);
/*fills entire canvas with one color*/
VLIBCDEF void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates rect without filling it*/
VLIBCDEF void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos1, vlibc_vec2d pos2, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates filled rect*/
VLIBCDEF void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d position, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates row*/
VLIBCDEF void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int width, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates column*/
VLIBCDEF void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int height, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates line*/
VLIBCDEF void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d start, vlibc_vec2d end, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates circle*/
VLIBCDEF void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates filled circle*/
VLIBCDEF void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates ellipse*/
VLIBCDEF void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates filled ellipse*/
VLIBCDEF void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates triangle*/
VLIBCDEF void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p3, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates filled triangle*/
VLIBCDEF void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);
/*creates figure with filled triangles*/
VLIBCDEF void vlibc_filled_figure(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, int num_of_vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data);

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

vlibc_rgba vlibc_f_rgba_to_rgba(vlibc_f_rgba rgba) {
	return (vlibc_rgba) {
		(vlibc_uint8_t) vlibc_clamp(rgba.r, 0, 255), (vlibc_uint8_t) vlibc_clamp(rgba.g, 0, 255), (vlibc_uint8_t) vlibc_clamp(rgba.b, 0, 255), (vlibc_uint8_t) vlibc_clamp(rgba.a, 0, 255)
	};
}

vlibc_uint32_t vlibc_rgba_to_hex(vlibc_rgba c) {
	return (vlibc_uint32_t)( (vlibc_uint8_t) c.r & 0xFF | ( (vlibc_uint8_t) c.g &0xFF) << 8 | ( (vlibc_uint8_t) c.b &0xFF) << 16 | ( (vlibc_uint8_t) c.a &0xFF) << 24 );
}

vlibc_rgba vlibc_hex_to_rgba(vlibc_uint32_t c) {
	return *(vlibc_rgba*)&c;
}

float vlibc_lerp(float a, float b, float t) {
	return a * (1.0 - t) + (b * t);
}

float vlibc_linearize_depth(float d, float near, float far) {
	return near * far / (far + d * (near - far));
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

double vlibc_tan(double x) {
	return vlibc_sin(x)/vlibc_cos(x);
}

float vlibc_rsqrt(float x) {
	unsigned int i = *(unsigned int*) &x;
	i  += 127 << 23;
	i >>= 1;
	return 1/(*(float*) &i);
}

float vlibc_sqrt(float x) {
	return 1/vlibc_rsqrt(x);
}

bool vlibc_in_bounds(vlibc_canvas *vlibcc, vlibc_vec2d p) {
	if (p.x > vlibcc->size.x || p.y > vlibcc->size.y || p.x < 0 || p.y < 0) return false;
	return true;
}

vlibc_vec3d vlibc_vec3d_cross(vlibc_vec3d a, vlibc_vec3d b) {
	return (vlibc_vec3d) {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
}

vlibc_vec3d vlibc_vec3d_proj(vlibc_vec3d v, vlibc_vec3d onto) {
	return vlibc_mul_vec3df(onto, vlibc_vec3d_dot(v, onto) / vlibc_vec3d_dot(onto, onto));
}

float vlibc_vec2d_dot(vlibc_vec2d a, vlibc_vec2d b) {
	return a.x*b.x + a.y*b.y;
}

float vlibc_vec3d_dot(vlibc_vec3d a, vlibc_vec3d b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float vlibc_vec4d_dot(vlibc_vec4d a, vlibc_vec4d b) {
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

vlibc_vec2d vlibc_vec2d_normalize(vlibc_vec2d v) {
	return (vlibc_vec2d) {
		.x = vlibc_rsqrt(vlibc_vec2d_dot(v,v)) * v.x,
		.y = vlibc_rsqrt(vlibc_vec2d_dot(v,v)) * v.y
	};
}

vlibc_vec3d vlibc_vec3d_normalize(vlibc_vec3d v) {
	return (vlibc_vec3d) {
		.x = vlibc_rsqrt(vlibc_vec3d_dot(v,v)) * v.x,
		.y = vlibc_rsqrt(vlibc_vec3d_dot(v,v)) * v.y,
		.z = vlibc_rsqrt(vlibc_vec3d_dot(v,v)) * v.z
	};
}

vlibc_vec4d vlibc_vec4d_normalize(vlibc_vec4d v) {
	return (vlibc_vec4d) {
		.x = vlibc_rsqrt(vlibc_vec4d_dot(v,v)) * v.x,
		.y = vlibc_rsqrt(vlibc_vec4d_dot(v,v)) * v.y,
		.z = vlibc_rsqrt(vlibc_vec4d_dot(v,v)) * v.z,
		.w = vlibc_rsqrt(vlibc_vec4d_dot(v,v)) * v.w
	};
}

float vlibc_vec2d_length(vlibc_vec2d p) {
	return vlibc_sqrt(p.x*p.x + p.y*p.y);
}

float vlibc_vec3d_length(vlibc_vec3d p) {
	return vlibc_sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

float vlibc_vec4d_length(vlibc_vec4d p) {
	return vlibc_sqrt(p.x*p.x + p.y*p.y + p.z*p.z + p.w*p.w);
}

vlibc_vec2d vlibc_vec2d_reflect(vlibc_vec2d i, vlibc_vec2d n) {
	float d = vlibc_vec2d_dot(n, i);
	return vlibc_sub_vec2d(i, vlibc_mul_vec2d((vlibc_vec2d){2.0, 2.0}, (vlibc_vec2d){d, d}));
}

vlibc_vec3d vlibc_vec3d_reflect(vlibc_vec3d i, vlibc_vec3d n) {
	float d = vlibc_vec3d_dot(n, i);
	return vlibc_sub_vec3d(i, vlibc_mul_vec3d((vlibc_vec3d){2.0, 2.0, 2.0}, (vlibc_vec3d){d, d, d}));
}

vlibc_vec4d vlibc_vec4d_reflect(vlibc_vec4d i, vlibc_vec4d n) {
	float d = vlibc_vec4d_dot(n, i);
	return vlibc_sub_vec4d(i, vlibc_mul_vec4d((vlibc_vec4d){2.0, 2.0, 2.0, 2.0}, (vlibc_vec4d){d, d, d, d}));
}

vlibc_vec2d vlibc_vec2d_negate(vlibc_vec2d x) {
	return (vlibc_vec2d){-x.x, -x.y};
}

vlibc_vec3d vlibc_vec3d_negate(vlibc_vec3d x) {
	return (vlibc_vec3d){-x.x, -x.y, -x.z};
}

vlibc_vec4d vlibc_vec4d_negate(vlibc_vec4d x) {
	return (vlibc_vec4d){-x.x, -x.y, -x.z, -x.w};
}

vlibc_vec2d vlibc_mul_vec2d(vlibc_vec2d a, vlibc_vec2d b) {
	return (vlibc_vec2d) {
		.x = a.x*b.x,
		.y = a.y*b.y
	};
}

vlibc_vec2d vlibc_mul_vec2df(vlibc_vec2d a, float b) {
	return (vlibc_vec2d) {
		.x = a.x*b,
		.y = a.y*b
	};
}

vlibc_vec3d vlibc_mul_vec3d(vlibc_vec3d a, vlibc_vec3d b) {
	return (vlibc_vec3d) {
		.x = a.x*b.x,
		.y = a.y*b.y,
		.z = a.z*b.z
	};
}

vlibc_vec3d vlibc_mul_vec3df(vlibc_vec3d a, float b) {
	return (vlibc_vec3d) {
		.x = a.x*b,
		.y = a.y*b,
		.z = a.z*b
	};
}

vlibc_vec4d vlibc_mul_vec4d(vlibc_vec4d a, vlibc_vec4d b) {
	return (vlibc_vec4d) {
		.x = a.x*b.x,
		.y = a.y*b.y,
		.z = a.z*b.z,
		.w = a.w*b.w
	};
}

vlibc_vec4d vlibc_mul_vec4df(vlibc_vec4d a, float b) {
	return (vlibc_vec4d) {
		.x = a.x*b,
		.y = a.y*b,
		.z = a.z*b,
		.w = a.w*b
	};
}

vlibc_vec2d vlibc_add_vec2d(vlibc_vec2d a, vlibc_vec2d b) {
	return (vlibc_vec2d) {
		.x = a.x+b.x,
		.y = a.y+b.y
	};
}

vlibc_vec2d vlibc_add_vec2df(vlibc_vec2d a, float b) {
	return (vlibc_vec2d) {
		.x = a.x+b,
		.y = a.y+b
	};
}

vlibc_vec3d vlibc_add_vec3d(vlibc_vec3d a, vlibc_vec3d b) {
	return (vlibc_vec3d) {
		.x = a.x+b.x,
		.y = a.y+b.y,
		.z = a.z+b.z
	};
}

vlibc_vec3d vlibc_add_vec3df(vlibc_vec3d a, float b) {
	return (vlibc_vec3d) {
		.x = a.x+b,
		.y = a.y+b,
		.z = a.z+b
	};
}

vlibc_vec4d vlibc_add_vec4d(vlibc_vec4d a, vlibc_vec4d b) {
	return (vlibc_vec4d) {
		.x = a.x+b.x,
		.y = a.y+b.y,
		.z = a.z+b.z,
		.w = a.w+b.w
	};
}

vlibc_vec4d vlibc_add_vec4df(vlibc_vec4d a, float b) {
	return (vlibc_vec4d) {
		.x = a.x+b,
		.y = a.y+b,
		.z = a.z+b,
		.w = a.w+b
	};
}

vlibc_vec2d vlibc_div_vec2d(vlibc_vec2d a, vlibc_vec2d b) {
	return (vlibc_vec2d) {
		.x = a.x/b.x,
		.y = a.y/b.y
	};
}

vlibc_vec2d vlibc_div_vec2df(vlibc_vec2d a, float b) {
	return (vlibc_vec2d) {
		.x = a.x/b,
		.y = a.y/b
	};
}

vlibc_vec3d vlibc_div_vec3d(vlibc_vec3d a, vlibc_vec3d b) {
	return (vlibc_vec3d) {
		.x = a.x/b.x,
		.y = a.y/b.y,
		.z = a.z/b.z
	};
}

vlibc_vec3d vlibc_div_vec3df(vlibc_vec3d a, float b) {
	return (vlibc_vec3d) {
		.x = a.x/b,
		.y = a.y/b,
		.z = a.z/b
	};
}

vlibc_vec4d vlibc_div_vec4d(vlibc_vec4d a, vlibc_vec4d b) {
	return (vlibc_vec4d) {
		.x = a.x/b.x,
		.y = a.y/b.y,
		.z = a.z/b.z,
		.w = a.w/b.w
	};
}

vlibc_vec4d vlibc_div_vec4df(vlibc_vec4d a, float b) {
	return (vlibc_vec4d) {
		.x = a.x/b,
		.y = a.y/b,
		.z = a.z/b,
		.w = a.w/b
	};
}

vlibc_vec2d vlibc_sub_vec2d(vlibc_vec2d a, vlibc_vec2d b) {
	return (vlibc_vec2d) {
		.x = a.x-b.x,
		.y = a.y-b.y
	};
}

vlibc_vec2d vlibc_sub_vec2df(vlibc_vec2d a, float b) {
	return (vlibc_vec2d) {
		.x = a.x-b,
		.y = a.y-b
	};
}

vlibc_vec3d vlibc_sub_vec3d(vlibc_vec3d a, vlibc_vec3d b) {
	return (vlibc_vec3d) {
		.x = a.x-b.x,
		.y = a.y-b.y,
		.z = a.z-b.z
	};
}

vlibc_vec3d vlibc_sub_vec3df(vlibc_vec3d a, float b) {
	return (vlibc_vec3d) {
		.x = a.x-b,
		.y = a.y-b,
		.z = a.z-b
	};
}

vlibc_vec4d vlibc_sub_vec4d(vlibc_vec4d a, vlibc_vec4d b) {
	return (vlibc_vec4d) {
		.x = a.x-b.x,
		.y = a.y-b.y,
		.z = a.z-b.z,
		.w = a.w-b.w
	};
}

vlibc_vec4d vlibc_sub_vec4df(vlibc_vec4d a, float b) {
	return (vlibc_vec4d) {
		.x = a.x-b,
		.y = a.y-b,
		.z = a.z-b,
		.w = a.w-b
	};
}

vlibc_vec2d vlibc_div_fvec2d(float b, vlibc_vec2d a) {
	return (vlibc_vec2d) {
		.x = b/a.x,
		.y = b/a.y
	};
}

vlibc_vec3d vlibc_div_fvec3d(float b, vlibc_vec3d a) {
	return (vlibc_vec3d) {
		.x = b/a.x,
		.y = b/a.y,
		.z = b/a.z
	};
}

vlibc_vec4d vlibc_div_fvec4d(float b, vlibc_vec4d a) {
	return (vlibc_vec4d) {
		.x = b/a.x,
		.y = b/a.y,
		.z = b/a.z,
		.w = b/a.w
	};
}

vlibc_vec2d vlibc_sub_fvec2d(float b, vlibc_vec2d a) {
	return (vlibc_vec2d) {
		.x = b-a.x,
		.y = b-a.y
	};
}

vlibc_vec3d vlibc_sub_fvec3d(float b, vlibc_vec3d a) {
	return (vlibc_vec3d) {
		.x = b-a.x,
		.y = b-a.y,
		.z = b-a.z
	};
}

vlibc_vec4d vlibc_sub_fvec4d(float b, vlibc_vec4d a) {
	return (vlibc_vec4d) {
		.x = b-a.x,
		.y = b-a.y,
		.z = b-a.z,
		.w = b-a.w
	};
}

bool vlibc_vec2d_equal(vlibc_vec2d a, vlibc_vec2d b) {
	return a.x == b.x && a.y == b.y;
}

bool vlibc_vec3d_equal(vlibc_vec3d a, vlibc_vec3d b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool vlibc_vec4d_equal(vlibc_vec4d a, vlibc_vec4d b) {
	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

bool vlibc_rgba_equal(vlibc_rgba a, vlibc_rgba b) {
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

bool vlibc_vertex_equal(vlibc_vertex a, vlibc_vertex b) {
	if (a.col_count != b.col_count) return false;
	if (a.pos.x != b.pos.x || a.pos.y != b.pos.y) return false;
	return true;
}

vlibc_mat4_t vlibc_mat4(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33) {
	return (vlibc_mat4_t) {
		.m[0][0] = m00, .m[1][0] = m10, .m[2][0] = m20, .m[3][0] = m30,
		.m[0][1] = m01, .m[1][1] = m11, .m[2][1] = m21, .m[3][1] = m31,
		.m[0][2] = m02, .m[1][2] = m12, .m[2][2] = m22, .m[3][2] = m32,
		.m[0][3] = m03, .m[1][3] = m13, .m[2][3] = m23, .m[3][3] = m33
	};
}

vlibc_mat4_t vlibc_mat4_identity() {
	return vlibc_mat4(
		1,  0,  0,  0,
		0,  1,  0,  0,
		0,  0,  1,  0,
		0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_translation(vlibc_vec3d offset) {
	return vlibc_mat4(
		1,  0,  0,  offset.x,
		0,  1,  0,  offset.y,
		0,  0,  1,  offset.z,
		0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_scaling(vlibc_vec3d scale) {
	float x = scale.x;
	float y = scale.y;
	float z = scale.z;
	return vlibc_mat4(
		x,  0,  0,  0,
		0,  y,  0,  0,
		0,  0,  z,  0,
		0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_rotation_x(float angle_in_rad) {
	float s = vlibc_sin(angle_in_rad);
	float c = vlibc_cos(angle_in_rad);
	return vlibc_mat4(
		1,  0,  0,  0,
		0,  c, -s,  0,
		0,  s,  c,  0,
		0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_rotation_y(float angle_in_rad) {
	float s = vlibc_sin(angle_in_rad);
	float c = vlibc_cos(angle_in_rad);
	return vlibc_mat4(
		 c,  0,  s,  0,
		 0,  1,  0,  0,
		-s,  0,  c,  0,
		 0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_rotation_z(float angle_in_rad) {
	float s = vlibc_sin(angle_in_rad);
	float c = vlibc_cos(angle_in_rad);
	return vlibc_mat4(
		 c, -s,  0,  0,
		 s,  c,  0,  0,
		 0,  0,  1,  0,
		 0,  0,  0,  1
	);
}

vlibc_mat4_t vlibc_mat4_rotation(float angle_in_rad, vlibc_vec3d axis) {
	vlibc_vec3d normalized_axis = vlibc_vec3d_normalize(axis);
	float x = normalized_axis.x, y = normalized_axis.y, z = normalized_axis.z;
	float c = vlibc_cos(angle_in_rad), s = vlibc_sin(angle_in_rad);
	
	return vlibc_mat4(
			c + x*x*(1-c),			x*y*(1-c) - z*s,	  x*z*(1-c) + y*s,	0,
			y*x*(1-c) + z*s,  		  c + y*y*(1-c),		y*z*(1-c) - x*s,	0,
			z*x*(1-c) - y*s,	  	  z*y*(1-c) + x*s,  	c + z*z*(1-c),	  0,
			0,						0,					0,					1
	);
}

vlibc_mat4_t vlibc_mat4_ortho(float left, float right, float bottom, float top, float back, float front) {
	float l = left, r = right, b = bottom, t = top, n = front, f = back;
	float tx = -(r + l) / (r - l);
	float ty = -(t + b) / (t - b);
	float tz = -(f + n) / (f - n);
	return vlibc_mat4(
		 2 / (r - l),  0,			0,			tx,
		 0,			2 / (t - b),  0,			ty,
		 0,			0,			2 / (f - n),  tz,
		 0,			0,			0,			1
	);
}

vlibc_mat4_t vlibc_mat4_perspective(float vertical_field_of_view_in_deg, float aspect_ratio, float near_view_distance, float far_view_distance) {
	float fovy_in_rad = vertical_field_of_view_in_deg / 180 * VLIBC_PI;
	float f = 1.0f / vlibc_tan(fovy_in_rad / 2.0f);
	float ar = aspect_ratio;
	float nd = near_view_distance, fd = far_view_distance;
	
	return vlibc_mat4(
		f / ar, 0,  0,				0,
		0,	  f,  0,				0,
		0,	  0, (fd+nd)/(nd-fd),  (2*fd*nd)/(nd-fd),
		0,	  0, -1,				0
	);
}

vlibc_mat4_t vlibc_mat4_look_at(vlibc_vec3d from, vlibc_vec3d to, vlibc_vec3d up) {
	vlibc_vec3d z = vlibc_mul_vec3df(vlibc_vec3d_normalize(vlibc_sub_vec3d(to, from)), -1);
	vlibc_vec3d x = vlibc_vec3d_normalize(vlibc_vec3d_cross(up, z));
	vlibc_vec3d y = vlibc_vec3d_cross(z, x);
	
	return vlibc_mat4(
		x.x, x.y, x.z, -vlibc_vec3d_dot(from, x),
		y.x, y.y, y.z, -vlibc_vec3d_dot(from, y),
		z.x, z.y, z.z, -vlibc_vec3d_dot(from, z),
		0,   0,   0,	1
	);
}

vlibc_mat4_t vlibc_mat4_transpose(vlibc_mat4_t matrix) {
	return vlibc_mat4(
		matrix.m00, matrix.m01, matrix.m02, matrix.m03,
		matrix.m10, matrix.m11, matrix.m12, matrix.m13,
		matrix.m20, matrix.m21, matrix.m22, matrix.m23,
		matrix.m30, matrix.m31, matrix.m32, matrix.m33
	);
}

vlibc_mat4_t vlibc_mat4_mul(vlibc_mat4_t a, vlibc_mat4_t b) {
	vlibc_mat4_t result;
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			float sum = 0;
			for(int k = 0; k < 4; k++) {
				sum += a.m[k][j] * b.m[i][k];
			}
			result.m[i][j] = sum;
		}
	}
	
	return result;
}

vlibc_mat4_t vlibc_mat4_invert_affine(vlibc_mat4_t matrix) {
	float m00 = matrix.m00,  m10 = matrix.m10,  m20 = matrix.m20,  m30 = matrix.m30;
	float m01 = matrix.m01,  m11 = matrix.m11,  m21 = matrix.m21,  m31 = matrix.m31;
	float m02 = matrix.m02,  m12 = matrix.m12,  m22 = matrix.m22,  m32 = matrix.m32;
	
	float c00 =   m11*m22 - m12*m21,   c10 = -(m01*m22 - m02*m21),  c20 =   m01*m12 - m02*m11;
	float c01 = -(m10*m22 - m12*m20),  c11 =   m00*m22 - m02*m20,   c21 = -(m00*m12 - m02*m10);
	float c02 =   m10*m21 - m11*m20,   c12 = -(m00*m21 - m01*m20),  c22 =   m00*m11 - m01*m10;
	
	float det = m00*c00 + m10*c10 + m20 * c20;
	if (VLIBC_ABS(float, det) < 0.00001)
		return vlibc_mat4_identity();

	float i00 = c00 / det,  i10 = c01 / det,  i20 = c02 / det;
	float i01 = c10 / det,  i11 = c11 / det,  i21 = c12 / det;
	float i02 = c20 / det,  i12 = c21 / det,  i22 = c22 / det;
	
	return vlibc_mat4(
		i00, i10, i20,  -(i00*m30 + i10*m31 + i20*m32),
		i01, i11, i21,  -(i01*m30 + i11*m31 + i21*m32),
		i02, i12, i22,  -(i02*m30 + i12*m31 + i22*m32),
		0,   0,   0,	  1
	);
}

vlibc_vec3d vlibc_mat4_mul_pos(vlibc_mat4_t matrix, vlibc_vec3d position) {
	vlibc_vec3d result = (vlibc_vec3d) {
		matrix.m00 * position.x + matrix.m10 * position.y + matrix.m20 * position.z + matrix.m30,
		matrix.m01 * position.x + matrix.m11 * position.y + matrix.m21 * position.z + matrix.m31,
		matrix.m02 * position.x + matrix.m12 * position.y + matrix.m22 * position.z + matrix.m32
	};
	
	float w = matrix.m03 * position.x + matrix.m13 * position.y + matrix.m23 * position.z + matrix.m33;
	if (w != 0 && w != 1)
		return (vlibc_vec3d){result.x / w, result.y / w, result.z / w};
	
	return result;
}

vlibc_vec3d vlibc_mat4_mul_dir(vlibc_mat4_t matrix, vlibc_vec3d direction) {
	vlibc_vec3d result = (vlibc_vec3d) {
		matrix.m00 * direction.x + matrix.m10 * direction.y + matrix.m20 * direction.z,
		matrix.m01 * direction.x + matrix.m11 * direction.y + matrix.m21 * direction.z,
		matrix.m02 * direction.x + matrix.m12 * direction.y + matrix.m22 * direction.z
	};
	
	float w = matrix.m03 * direction.x + matrix.m13 * direction.y + matrix.m23 * direction.z;
	if (w != 0 && w != 1)
		return (vlibc_vec3d){result.x / w, result.y / w, result.z / w};
	
	return result;
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

vlibc_fragment_shader_t vlibc_create_fragment_shader(vlibc_uint32_t (*func)(vlibc_vec2d, vlibc_rgba, vlibc_shader_data_t*)) {
	return (vlibc_fragment_shader_t) {
		.func = func
	};
}

vlibc_shader_data_t vlibc_create_shader_data(float *shader_data, vlibc_size_t shader_data_size, vlibc_f_rgba *passthrough_data) {
	return (vlibc_shader_data_t) {
		shader_data,
		passthrough_data,
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
	if (shader_data == vlibc_nullptr) return -1;
	float x = *(shader_data+index);
	return 
		x >= 0
			?(int)(x + 0.5)
			:(int)(x - 0.5);
}

vlibc_vec2d vlibc_shader_data_parse_vec2d(float *shader_data, int index) {
	if (shader_data == vlibc_nullptr) return VLIBC_VEC2D_NULL;
	return (vlibc_vec2d) {
		.x = *(shader_data+index),
		.y = *(shader_data+index+1),
	};
}

vlibc_vec3d vlibc_shader_data_parse_vec3d(float *shader_data, int index) {
	if (shader_data == vlibc_nullptr) return VLIBC_VEC3D_NULL;
	return (vlibc_vec3d) {
		.x = *(shader_data+index),
		.y = *(shader_data+index+1),
		.z = *(shader_data+index+2),
	};
}

vlibc_vec4d vlibc_shader_data_parse_vec4d(float *shader_data, int index) {
	if (shader_data == vlibc_nullptr) return VLIBC_VEC4D_NULL;
	return (vlibc_vec4d) {
		.x = *(shader_data+index),
		.y = *(shader_data+index+1),
		.z = *(shader_data+index+2),
		.w = *(shader_data+index+3),
	};
}

vlibc_vertex vlibc_shader_data_parse_vertex(float *shader_data, int index) {
	vlibc_vec2d p = (vlibc_vec2d){shader_data[index], shader_data[index+1]};
	vlibc_rgba c = (vlibc_rgba){shader_data[index+2], shader_data[index+3], shader_data[index+4], shader_data[index+5]};
	return (vlibc_vertex) {
		p, vlibc_nullptr, 0,
	};
}

vlibc_rgba vlibc_shader_data_parse_rgba(float *shader_data, int index) {
	if (shader_data == vlibc_nullptr) return VLIBC_RGBA_NULL;
	return (vlibc_rgba) {
		.r = *(shader_data+index),
		.g = *(shader_data+index+1),
		.b = *(shader_data+index+2),
		.a = *(shader_data+index+3),
	};
}

vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2, float phase) {
	vlibc_rgba output = (vlibc_rgba) {0, 0, 0, 0};
	output.r = vlibc_lerp(c1.r, c2.r, phase);
	output.g = vlibc_lerp(c1.g, c2.g, phase);
	output.b = vlibc_lerp(c1.b, c2.b, phase);
	output.a = vlibc_lerp(c1.a, c2.a, phase);
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

void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos1, vlibc_vec2d pos2, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_uint32_t conv_c = vlibc_rgba_to_hex(color);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos1.y}, (vlibc_vec2d){pos2.x, pos1.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos1.y}, (vlibc_vec2d){pos1.x, pos2.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos1.x, pos2.y}, (vlibc_vec2d){pos2.x, pos2.y}, shader, shader_data);
	vlibc_line(vlibcc, color, (vlibc_vec2d){pos2.x, pos1.y}, (vlibc_vec2d){pos2.x, pos2.y}, shader, shader_data);
}

void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d position, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_filled_triangle(vlibcc, color, position, vertices, shader, shader_data);
	vlibc_filled_triangle(vlibcc, color, position, vertices + 1, shader, shader_data);
}

void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int width, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int height, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d start, vlibc_vec2d end, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int r, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, int rx, int ry, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vec2d p1, vlibc_vec2d p2, vlibc_vec2d p3, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
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

void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	vlibc_vertex p1 = vertices[0];
	vlibc_vertex p2 = vertices[1];
	vlibc_vertex p3 = vertices[2];

	if (p2.col_count != p1.col_count || p3.col_count != p1.col_count) {
		return;
	}

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

					float r = w0 * p1.col[0].r + w1 * p2.col[0].r + w2 * p3.col[0].r;
					float g = w0 * p1.col[0].g + w1 * p2.col[0].g + w2 * p3.col[0].g;
					float b = w0 * p1.col[0].b + w1 * p2.col[0].b + w2 * p3.col[0].b;

					if (shader_data->passthrough_data) {
						for (int i = 0; i < p1.col_count; i++) {
							vlibc_f_rgba p1_target_color = p1.col[i];
							vlibc_f_rgba p2_target_color = p2.col[i];
							vlibc_f_rgba p3_target_color = p3.col[i];


							float r = w0 * p1_target_color.r + w1 * p2_target_color.r + w2 * p3_target_color.r;
							float g = w0 * p1_target_color.g + w1 * p2_target_color.g + w2 * p3_target_color.g;
							float b = w0 * p1_target_color.b + w1 * p2_target_color.b + w2 * p3_target_color.b;
							float a = w0 * p1_target_color.a + w1 * p2_target_color.a + w2 * p3_target_color.a;

							shader_data->passthrough_data[i] = (vlibc_f_rgba){r, g, b, a};
						}
					}
					ncolor = (vlibc_rgba) {
						.r = r,
						.g = g,
						.b = b,
						.a = color.a
					};

					color = vlibc_hex_to_rgba(shader->func(p, ncolor, shader_data));
				}
				if (color.a != 0) __vlibc_fast_put_pixel(vlibcc, color, p);
			}
		}
	}
}

void vlibc_filled_figure(vlibc_canvas* vlibcc, vlibc_rgba color, vlibc_vec2d pos, vlibc_vertex *vertices, int num_of_vertices, vlibc_fragment_shader_t *shader, vlibc_shader_data_t *shader_data) {
	if (vlibcc == vlibc_nullptr) return;
	for (vlibc_size_t i = 0; i+2 < num_of_vertices; i++) {
		vlibc_filled_triangle(vlibcc, color, pos, vertices+i, shader, shader_data);
	}
}

#endif