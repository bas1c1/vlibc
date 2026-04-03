/*
 * vlibc - header-only no-std crossplatform simple graphics library 
 * Copyright (c) 2026 bas1c1
 * Licensed under AGPLv3.
 */

#define VLIBC_FONTS
#define __VLIBC_ARDUINO_SERIAL__
#include "../vlibc.h"
#include "vlibc_arduino_serial.h"

#define WIDTH 21
#define HEIGHT 21

vlibc_canvas canvas;
static float current_angle = 0.0f;

void setup() {
  Serial.begin(115200);
  canvas = vlibc_arduino_serial_alloc_canvas((vlibc_vec2d){WIDTH, HEIGHT});
}

void loop() {
  current_angle += 0.02f;

  vlibc_fill(&canvas, (vlibc_rgba){0, 0, 0, 255}, vlibc_nullptr, vlibc_nullptr);

  vlibc_mat4_t rotation = vlibc_mat4_rotation_z(current_angle);
  
  vlibc_vec3d center;
  center.x = WIDTH / 2.0f; center.y = HEIGHT / 2.0f; center.z = 0;

  float size = 5.0f;

  vlibc_vec3d corners[4] = {
    {-size, -size, 0},
    { size, -size, 0},
    { size,  size, 0},
    {-size,  size, 0}
  };

  vlibc_vertex vertices[4];
  vlibc_f_rgba color_data;
  color_data.r = 255; color_data.g = 255; color_data.b = 255; color_data.a = 255;

  for (int i = 0; i < 4; i++) {
    vlibc_vec3d rotated = vlibc_mat4_mul_dir(rotation, corners[i]);
    
    vertices[i].pos.x = rotated.x + center.x;
    vertices[i].pos.y = rotated.y + center.y;
    vertices[i].col = &color_data;
    vertices[i].col_count = 1;
  }

  vlibc_rgba white;
  white.r = 255; white.g = 255; white.b = 255; white.a = 255;

  vlibc_filled_figure(&canvas, white, VLIBC_VEC2D_NULL, vertices, 4, vlibc_nullptr, vlibc_nullptr);

  vlibc_arduino_serial_flush_canvas(&canvas);
}