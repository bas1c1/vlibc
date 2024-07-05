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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

VLIBCDEF char* nullptr = (void*)0;

typedef struct {
	int x, y;
} VEC2D;

typedef struct {
	uint32_t *pixels;
	VEC2D size;
} vlibc_canvas;

typedef struct {
	uint8_t r:8, g:8, b:8, a:8;
} vlibc_rgba;

/*math functions*/
VLIBCDEF int vlibc_swap(int *f, int *s);
VLIBCDEF int vlibc_abs(int n);
VLIBCDEF float vlibc_cross_product(VEC2D p1, VEC2D p2);

VLIBCDEF uint32_t vlibc_rgba_to_hex(vlibc_rgba c);
VLIBCDEF vlibc_rgba vlibc_hex_to_rgba(uint32_t c);

/*gets average of red, green, blue and alpha and multiplies it by weight*/
VLIBCDEF vlibc_rgba vlibc_mix_colors(vlibc_rgba c1, vlibc_rgba c2);
/*puts a pixel on position*/
VLIBCDEF void vlibc_put_pixel(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos);
/*gets a pixel on position*/
VLIBCDEF uint32_t vlibc_get_pixel(vlibc_canvas *vlibcc, VEC2D pos, int inversion);
/*fills entire canvas with one color*/
VLIBCDEF void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color);
/*creates rect without filling it*/
VLIBCDEF void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2);
/*creates filled rect*/
VLIBCDEF void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2);
/*creates row*/
VLIBCDEF void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int width);
/*creates column*/
VLIBCDEF void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int height);
/*creates line*/
VLIBCDEF void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D start, VEC2D end);
/*creates straight line*/
VLIBCDEF void vlibc_straight_line(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D start, VEC2D end, int direction);
/*creates circle*/
VLIBCDEF void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r);
/*creates filled circle*/
VLIBCDEF void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r);
/*creates ellipse*/
VLIBCDEF void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry);
/*creates filled ellipse*/
VLIBCDEF void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry);
/*creates triangle*/
VLIBCDEF void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, VEC2D p1, VEC2D p2, VEC2D p3);
/*creates filled triangle*/
VLIBCDEF void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, VEC2D p1, VEC2D p2, VEC2D p3);

#endif

#ifdef __VLIBC_IMPL__

int vlibc_swap(int *f, int *s) {
	int t = 0;
	t = *f;
	*f = *s;
	*s = t;
}

int vlibc_abs(int n) {
	if (n < 0) {
		return n - n*2;
	}
	else {
		return n;
	}
}

float vlibc_cross_product(VEC2D p1, VEC2D p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

uint32_t vlibc_rgba_to_hex(vlibc_rgba c) {
	return (uint32_t)( c.r&0xFF | (c.g&0xFF) << 8 | (c.b&0xFF) << 16 | (c.a&0xFF) << 24 );
}

vlibc_rgba vlibc_hex_to_rgba(uint32_t c) {
	return *(vlibc_rgba*)&c;
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
	vlibcc->pixels[pos.x*vlibcc->size.x + pos.y] = vlibc_rgba_to_hex(color);
}

uint32_t vlibc_get_pixel(vlibc_canvas *vlibcc, VEC2D pos, int inversion) {
	if (inversion == 1)
		return vlibcc->pixels[pos.x*vlibcc->size.x + pos.y];
	return vlibcc->pixels[pos.y*vlibcc->size.x + pos.x];
}

void vlibc_fill(vlibc_canvas* vlibcc, vlibc_rgba color) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	size_t size = vlibcc->size.x * vlibcc->size.y;
	for (size_t i = 0; i < size; i++) {
		vlibcc->pixels[i] = conv_c;
	}
}

void vlibc_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	vlibc_line(vlibcc, color, (VEC2D){pos1.x, pos1.y}, (VEC2D){pos2.x, pos1.y});
	vlibc_line(vlibcc, color, (VEC2D){pos1.x, pos1.y}, (VEC2D){pos1.x, pos2.y});
	vlibc_line(vlibcc, color, (VEC2D){pos1.x, pos2.y}, (VEC2D){pos2.x, pos2.y});
	vlibc_line(vlibcc, color, (VEC2D){pos2.x, pos1.y}, (VEC2D){pos2.x, pos2.y});
}

void vlibc_filled_rect(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos1, VEC2D pos2) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);

	for (int x = pos1.x; x < pos2.x; x++) {
		for (int y = pos1.y; y < pos2.y; y++) {
			vlibcc->pixels[y*vlibcc->size.x + x] = conv_c;
		}
	}
}

void vlibc_row(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int width) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	for (int i = 0; i < width; i++)
		vlibcc->pixels[(pos.x+i)*vlibcc->size.x + pos.y] = conv_c;
}

void vlibc_column(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int height) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	for (int i = 0; i < height; i++)
		vlibcc->pixels[pos.x*vlibcc->size.x + (pos.y+height)] = conv_c;
}

void vlibc_line(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D start, VEC2D end) {
	uint32_t conv_c = vlibc_rgba_to_hex(color);
	int dx = end.x - start.x;
    int dy = end.y - start.y;

    if (dx == 0 && dy == 0) {
    	vlibcc->pixels[start.x*vlibcc->size.x + start.y] = conv_c;
        return;
    }

    if (vlibc_abs(dx) > vlibc_abs(dy)) {
        if (start.x > end.x) {
            vlibc_swap(&start.x, &end.x);
            vlibc_swap(&start.y, &end.y);
        }

        for (int x = start.x; x <= end.x; ++x) {
            int y = dy*(x - start.x)/dx + start.y;
            vlibcc->pixels[x*vlibcc->size.x + y] = conv_c;
        }
    } else {
        if (start.y > end.y) {
            vlibc_swap(&start.x, &end.x);
            vlibc_swap(&start.y, &end.y);
        }

        for (int y = start.y; y <= end.y; ++y) {
            int x = dx*(y - start.y)/dy + start.x;
            vlibcc->pixels[x*vlibcc->size.x + y] = conv_c;
        }
    }
}

void vlibc_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r) {
	pos.x += r;
	pos.y += r;
	int x = 0, y = r;
    int d = 3 - 2 * r;
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y+y});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y+y});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y-y});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y-y});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+y, pos.y+x});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-y, pos.y+x});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+y, pos.y-x});
    vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-y, pos.y-x});
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
        vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y+y});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y+y});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y-y});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y-y});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+y, pos.y+x});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-y, pos.y+x});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+y, pos.y-x});
    	vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-y, pos.y-x});
    }
}

void vlibc_filled_circle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int r) {
	pos.x += r;
	pos.y += r;
	int x = r;
    int y = 0;
    int xChange = 1 - (r << 1);
    int yChange = 0;
    int radiusError = 0;

    while (x >= y)
    {
        for (int i = pos.x - x; i <= pos.x + x; i++)
        {
            vlibc_put_pixel(vlibcc, color, (VEC2D){i, pos.y + y});
            vlibc_put_pixel(vlibcc, color, (VEC2D){i, pos.y - y});
        }
        for (int i = pos.x - y; i <= pos.x + y; i++)
        {
            vlibc_put_pixel(vlibcc, color, (VEC2D){i, pos.y + x});
            vlibc_put_pixel(vlibcc, color, (VEC2D){i, pos.y - x});
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

void vlibc_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry) {
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

	while (y>=0 && x<=rx) {
		vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y+y});
		if (x!=0 || y!=0)
			vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y-y});
		if (x!=0 && y!=0) {
			vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x+x, pos.y-y});
			vlibc_put_pixel(vlibcc, color, (VEC2D){pos.x-x, pos.y+y});
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

void vlibc_filled_ellipse(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, int rx, int ry) {
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
			vlibc_row(vlibcc, color, (VEC2D){pos.x-x, pos.y-y}, width);
			if (y!=0)
				vlibc_row(vlibcc, color, (VEC2D){pos.x-x, pos.y+y}, width);
			incy();
		}
		else {
			vlibc_row(vlibcc, color, (VEC2D){pos.x-x, pos.y-y}, width);
			if (y!=0)
				vlibc_row(vlibcc, color, (VEC2D){pos.x-x, pos.y+y}, width);
			incx();
			incy();
			width += 2;
		}
	}
	if (ry == 0)
		vlibc_row(vlibcc, color, (VEC2D){pos.x-rx, pos.y}, 2*rx+1);
}

#undef incx
#undef incy

void vlibc_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, VEC2D p1, VEC2D p2, VEC2D p3) {
	p1.x += pos.x;
	p1.y += pos.y;

	p2.x += pos.x;
	p2.y += pos.y;

	p3.x += pos.x;
	p3.y += pos.y;

	vlibc_line(vlibcc, color, p1, p2);
	vlibc_line(vlibcc, color, p2, p3);
	vlibc_line(vlibcc, color, p3, p1);
}

void vlibc_filled_triangle(vlibc_canvas* vlibcc, vlibc_rgba color, VEC2D pos, VEC2D p1, VEC2D p2, VEC2D p3) {
	p1.x += pos.x;
	p1.y += pos.y;

	p2.x += pos.x;
	p2.y += pos.y;

	p3.x += pos.x;
	p3.y += pos.y;

	int maxX = MAX(p1.x, MAX(p2.x, p3.x));
	int minX = MIN(p1.x, MIN(p2.x, p3.x));
	int maxY = MAX(p1.y, MAX(p2.y, p3.y));
	int minY = MIN(p1.y, MIN(p2.y, p3.y));

	VEC2D vs1 = (VEC2D){p2.x - p1.x, p2.y - p1.y};
	VEC2D vs2 = (VEC2D){p3.x - p1.x, p3.y - p1.y};

	for (int x = minX; x <= maxX; x++) {
		for (int y = minY; y <= maxY; y++) {
			VEC2D q = (VEC2D){x - p1.x, y - p1.y};

			float s = (float)vlibc_cross_product(q, vs2) / vlibc_cross_product(vs1, vs2);
			float t = (float)vlibc_cross_product(vs1, q) / vlibc_cross_product(vs1, vs2);

			if ( (s >= 0) && (t >= 0) && (s + t <= 1)) 
				vlibc_put_pixel(vlibcc, color, (VEC2D){x, y});
		}
	}
}

#endif