#ifndef __VLIBC__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#define UINT8_TT /* uint8_t */;
#define UINT16_TT /* uint16_t */;
#define UINT32_TT /* uint32_t */;
#define UINT64_TT /* uint64_t */;

#define VLIBCDEF static const

VLIBCDEF char* nullptr = (void*)0;

typedef struct {
	uint32_t *pixels;
	int width, height;
	int step;
} vlibc_canvas;

#define VLIBC_GET_PIXEL(vlibcc, x, y) (vlibcc.pixels[y*vlibcc.step + x])

typedef struct {
	uint8_t r, g, b, a;
} vlibc_rgba;

#define VLIBC_GET_COLOR_RED(c)       	   UINT32_TT   (((c)&0x000000FF)>>(8*0))
#define VLIBC_GET_COLOR_GREEN(c)           UINT32_TT   (((c)&0x0000FF00)>>(8*1))
#define VLIBC_GET_COLOR_BLUE(c)            UINT32_TT   (((c)&0x00FF0000)>>(8*2))
#define VLIBC_GET_COLOR_ALPHA(c)           UINT32_TT   (((c)&0xFF000000)>>(8*3))
#define VLIBC_GET_COLOR_RGBA(r, g, b, a)   UINT32_TT   ((((r)&0xFF)<<(8*0)) | (((g)&0xFF)<<(8*1)) | (((b)&0xFF)<<(8*2)) | (((a)&0xFF)<<(8*3)))

VLIBCDEF uint32_t rgba_to_hex(vlibc_rgba c);
VLIBCDEF vlibc_rgba hex_to_rgba(uint32_t c);

/*gets average of red, green, blue and alpha and multiplies it by weight*/
VLIBCDEF vlibc_rgba mix_colors(vlibc_rgba c1, vlibc_rgba c2);
/*puts a pixel on x, y coords*/
VLIBCDEF void put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, int x, int y);
/*fills entire canvas with one color*/
VLIBCDEF void fill(vlibc_canvas* vlibcc, vlibc_rgba color);

#define __VLIBC__
#endif