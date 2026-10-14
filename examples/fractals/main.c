/*
 * vlibc - header-only no-std crossplatform simple graphics library
 * Copyright (c) 2026 bas1c1
 * Licensed under AGPLv3.
 */

#define __VLIBC_WINDOWS_IMPL__
#include "vlibc_windows.h"

#define W    600
#define H    600
#define ITER 200

typedef struct {
    float r;
    float i;
} complex;

complex cadd(complex a, complex b) { return (complex){a.r + b.r, a.i + b.i}; }
complex cmul(complex a, complex b) { return (complex){a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r}; }
float   cabs(complex a)            { return a.r*a.r + a.i*a.i; }

vlibc_canvas canvas;

vlibc_uint32_t fractal_buf[W * H];

int mode = 0;
complex view_min = {-2, -2};
complex view_max = {2, 2};
complex jc = {-0.745, -0.135};

bool mouse_on = 0;
vlibc_vec2d mouse_start = {0, 0};
vlibc_vec2d mouse_curr = {0, 0};

bool render_request = 1;

vlibc_uint32_t make_color(int i) {
    float t = (float)i / ITER;

    vlibc_rgba c;
    c.r = (unsigned char)(127 + 127 * vlibc_sin(6.28f * t));
    c.g = (unsigned char)(127 + 127 * vlibc_sin(6.28f * (t + 0.33f)));
    c.b = (unsigned char)(127 + 127 * vlibc_sin(6.28f * (t + 0.67f)));
    c.a = 255;

    return vlibc_rgba_to_hex(c);
}

vlibc_uint32_t julia_cubic(complex z) {
    for (int i = 0; i < ITER; i++) {
        //z^3 + z*c + c
        z = cadd(cadd(cmul(cmul(z, z), z), cmul(z, jc)), jc);
        if (cabs(z) > 4.0f) {
            return make_color(i);
        }
    }
    return 0x000000;
}

vlibc_uint32_t julia(complex z) {
    for (int i = 0; i < ITER; i++) {
        //z^2 + c
        z = cadd(cmul(z, z), jc);
        if (cabs(z) > 4.0f) {
            return make_color(i);
        }
    }
    return 0x000000;
}

vlibc_uint32_t mandelbrot(complex c) {
    complex z = (complex){0, 0};
    for (int i = 0; i < ITER; i++) {
        //z^2 + c
        z = cadd(cmul(z, z), c);
        if (cabs(z) > 4.0f) {
            return make_color(i);
        }
    }
    return 0x000000;
}

void render_fractal(void) {
    float re_span = view_max.r - view_min.r;
    float im_span = view_max.i - view_min.i;
    complex c = (complex){0, 0};
    for (int y = 0; y < H; y++) {
        c.i = view_max.i - (float)y / H * im_span;
        for (int x = 0; x < W; x++) {
            c.r = view_min.r + (float)x / W * re_span;
            if (mode == 0) {
                fractal_buf[y * W + x] = mandelbrot(c);
            } else if (mode == 1) {
                fractal_buf[y * W + x] = julia(c);
            } else if (mode == 2) {
                fractal_buf[y * W + x] = julia_cubic(c);
            }
        }
    }
}

void handle_input(void) {
    static int last_lb = 0;
    POINT p;
    HWND hwnd;

    if (GetAsyncKeyState('1') & 1) { mode = 0; render_request = 1; }
    if (GetAsyncKeyState('2') & 1) { mode = 1; render_request = 1; }
    if (GetAsyncKeyState('3') & 1) { mode = 2; render_request = 1; }

    if (GetAsyncKeyState('R') & 1) {
        view_min = (complex){-2, -2};
        view_max = (complex){2, 2};
        render_request = 1;
    }

    if ((GetAsyncKeyState(VK_RETURN) & 1) || (GetAsyncKeyState(VK_F5) & 1))
        render_request = 1;

    if (GetAsyncKeyState(VK_OEM_PLUS) & 1) {
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) jc.i += 0.001f;
        else                                     jc.r += 0.001f;
    }
    if (GetAsyncKeyState(VK_OEM_MINUS) & 1) {
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000) jc.i -= 0.001f;
        else                                     jc.r -= 0.001f;
    }

    GetCursorPos(&p);
    hwnd = GetForegroundWindow();
    if (hwnd) ScreenToClient(hwnd, &p);

    float mx = (float)p.x;
    float my = (float)p.y;
    if (mx < 0) mx = 0; if (mx >= W) mx = W - 1;
    if (my < 0) my = 0; if (my >= H) my = H - 1;

    int lb = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

    if (lb && !last_lb) {
        mouse_on = 1;
        mouse_start.x = mouse_curr.x = mx;
        mouse_start.y = mouse_curr.y = my;
    }
    else if (lb && mouse_on) {
        float dx = mx - mouse_start.x;
        float dy = my - mouse_start.y;
        float size = VLIBC_MIN(VLIBC_ABS(float, dx), VLIBC_ABS(float, dy));
        mouse_curr.x = mouse_start.x + (dx >= 0 ? size : -size);
        mouse_curr.y = mouse_start.y + (dy >= 0 ? size : -size);
    }
    else if (!lb && last_lb && mouse_on) {
        mouse_on = 0;

        float x0 = VLIBC_MIN(mouse_start.x, mouse_curr.x), x1 = VLIBC_MAX(mouse_start.x, mouse_curr.x);
        float y0 = VLIBC_MIN(mouse_start.y, mouse_curr.y), y1 = VLIBC_MAX(mouse_start.y, mouse_curr.y);

        if (x1 - x0 >= 3 && y1 - y0 >= 3) {
            float re_span = view_max.r - view_min.r;
            float im_span = view_max.i - view_min.i;

            float nr0 = view_min.r + x0 / W * re_span;
            float nr1 = view_min.r + x1 / W * re_span;
            float ni1 = view_max.i - y0 / H * im_span;
            float ni0 = view_max.i - y1 / H * im_span;

            view_min = (complex){nr0, ni0};
            view_max = (complex){nr1, ni1};

            render_request = 1;
        }
    }
    last_lb = lb;
}

void draw_info(void) {
    char buf[32];
    for (int i = 0; i < 32; i++)
        buf[i] = ' ';

    buf[0] = 'R';
    sprintf((char*)(buf+2), "%.3f", jc.r);
    buf[12] = 'I';
    sprintf((char*)(buf+14), "%.3f", jc.i);
    vlibc_text(&canvas, (vlibc_rgba){255, 255, 255, 255}, (vlibc_vec2d){5, 5}, 2, buf, 22, vlibc_nullptr, vlibc_nullptr);
}

void display(void) {
    handle_input();

    if (render_request) {
        render_request = 0;
        render_fractal();
    }

    memcpy(canvas.pixels, fractal_buf, sizeof(fractal_buf));

    if (mouse_on) {
        int x0 = (int)VLIBC_MIN(mouse_start.x, mouse_curr.x), x1 = (int)VLIBC_MAX(mouse_start.x, mouse_curr.x);
        int y0 = (int)VLIBC_MIN(mouse_start.y, mouse_curr.y), y1 = (int)VLIBC_MAX(mouse_start.y, mouse_curr.y);
        vlibc_rect(&canvas, (vlibc_rgba){255, 255, 255, 255}, (vlibc_vec2d){x0, y0}, (vlibc_vec2d){x1, y1}, vlibc_nullptr, vlibc_nullptr);
    }

    draw_info();
}

int main(int argc, char* argv[]) {
    canvas = vlibc_windows_alloc_canvas((vlibc_vec2d){W, H});
    __vlibc_windows_canvas = &canvas;

    vlibc_windows_create_window("test", W, H);
    vlibc_windows_set_canvas(&canvas);

    vlibc_windows_start(display);
    return 0;
}
