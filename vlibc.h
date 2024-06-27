#ifndef __VLIBC__
#define __VLIBC__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef long unsigned int size_t;

#define UINT8_TT /* uint8_t */;
#define UINT16_TT /* uint16_t */;
#define UINT32_TT /* uint32_t */;
#define UINT64_TT /* uint64_t */;

#define VLIBCDEF static const

VLIBCDEF char* nullptr = (void*)0;

typedef struct {
	int x, y;
} VEC2D;

typedef struct {
	uint32_t *pixels;
	VEC2D size;
	int step;
} vlibc_canvas;

/*uint32_t vlibc_get_pixel(vlibc_canvas vlibcc, VEC2D pos);*/
#define VLIBC_GET_PIXEL(vlibcc, pos) vlibcc->pixels[pos.y*vlibcc->step + pos.x]

typedef struct {
	uint8_t r:8, g:8, b:8, a:8;
} vlibc_rgba;

#define VLIBC_GET_COLOR_RED(c)    UINT32_TT  (((c)&0x000000FF)>>(8*0))
#define VLIBC_GET_COLOR_GREEN(c)  UINT32_TT  (((c)&0x0000FF00)>>(8*1))
#define VLIBC_GET_COLOR_BLUE(c)   UINT32_TT  (((c)&0x00FF0000)>>(8*2))
#define VLIBC_GET_COLOR_ALPHA(c)  UINT32_TT  (((c)&0xFF000000)>>(8*3))

VLIBCDEF uint32_t vlibc_rgba_to_hex(vlibc_rgba c);
VLIBCDEF vlibc_rgba vlibc_hex_to_rgba(uint32_t c);

/*creates sub-canvas*/
VLIBCDEF vlibc_canvas vlibc_subcanvas(vlibc_canvas* vlibcc, VEC2D size, VEC2D pos, int step);
/*gets average of red, green, blue and alpha and multiplies it by weight*/
VLIBCDEF vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2);
/*puts a pixel on position*/
VLIBCDEF void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos);
/*fills entire canvas with one color*/
VLIBCDEF void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color);
/*creates rect without filling it*/
VLIBCDEF void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2);
/*creates filled rect*/
VLIBCDEF void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2);
/*creates line*/
VLIBCDEF void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D start, VEC2D end);
/*creates circle*/
VLIBCDEF void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r);
/*creates ellipse*/
VLIBCDEF void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry);

#endif

#define __VLIBC_IMPL__

#ifdef __VLIBC_IMPL__

uint32_t vlibc_rgba_to_hex(vlibc_rgba c) {
	return (uint32_t)( c.r&0xFF | (c.g&0xFF) << 8 | (c.b&0xFF) << 16 | (c.a&0xFF) << 24 );
}

vlibc_rgba vlibc_hex_to_rgba(uint32_t c) {
	return *(vlibc_rgba*)&c;
}

vlibc_canvas vlibc_subcanvas(vlibc_canvas* vlibcc, VEC2D size, VEC2D pos, int step) {
	return (vlibc_canvas) {
		(uint32_t*) &VLIBC_GET_PIXEL(vlibcc, pos),
		size,
		step
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

void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos) {
	vlibcc->pixels[pos.y*vlibcc->step + pos.x] = vlibc_rgba_to_hex(color);
}

void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	size_t size = vlibcc->size.x * vlibcc->size.y;
	for (size_t i = 0; i < size; i++) {
		vlibcc->pixels[i] = conv_c;
	}
}

void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2) {
	
}

void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2) {
	
}

void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D start, VEC2D end) {
	
}

void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r) {
	
}

void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry) {
	
}

#endif