/*
 * vlibc - header-only no-std crossplatform simple graphics library 
 * Copyright (c) 2026 bas1c1
 * Licensed under AGPLv3.
 */

#define __VLIBC_IMPL__
#define VLIBC_FONTS
#define VLIBC_PIXEL_SIZE_8
#include "../vlibc.h"

#ifndef __VLIBC_ARDUINO_SERIAL__
#define __VLIBC_ARDUINO_SERIAL__

VLIBCDEF vlibc_canvas vlibc_arduino_serial_alloc_canvas(vlibc_vec2d size);
VLIBCDEF int vlibc_arduino_serial_to_grayscale(vlibc_rgba c);
VLIBCDEF char vlibc_arduino_serial_character_grayscale(int gray_scale);
VLIBCDEF void vlibc_arduino_serial_flush_canvas(vlibc_canvas *canvas);
VLIBCDEF void vlibc_arduino_serial_cursor_gotoxy(int x, int y);
VLIBCDEF void vlibc_arduino_serial_clear_screen();

#endif

#ifdef __VLIBC_ARDUINO_SERIAL__

static float vlibc_arduino_serial_deltaTime = 0;

vlibc_canvas vlibc_arduino_serial_alloc_canvas(vlibc_vec2d size) {
  vlibc_pixel_t *graph = (vlibc_pixel_t*)malloc((size.x+1)*(size.y+1)*(sizeof(vlibc_pixel_t)));

  for (int i = 0; i < size.x * size.y; i++) {
    graph[i] = 0;
  }

  vlibc_canvas canvas;
  canvas.pixels = graph;
  canvas.size = size;
  canvas.offsize = size;
  canvas.offx = 0;
  canvas.offy = 0;

  return canvas;
}

int vlibc_arduino_serial_to_grayscale(vlibc_rgba c) {
  return (c.r + c.g + c.b)/3;
}

char vlibc_arduino_serial_character_grayscale(int gray_scale) {
  if (gray_scale > 225) return '@';
  if (gray_scale > 200) return '%';
  if (gray_scale > 175) return '#';
  if (gray_scale > 150) return '*';
  if (gray_scale > 125) return '+';
  if (gray_scale > 100) return '=';
  if (gray_scale > 75) return '-';
  if (gray_scale > 50) return ':';
  if (gray_scale > 15) return '.';
  return ' ';
}

void vlibc_arduino_serial_flush_canvas(vlibc_canvas *canvas) {
  vlibc_uint64_t current_ticks = millis();
  
  for (int i = 0; i < canvas->size.x; i++) {
    for (int j = 0; j < canvas->size.y; j++) {
      Serial.print(
        vlibc_arduino_serial_character_grayscale(
            vlibc_arduino_serial_to_grayscale(
                     vlibc_hex_to_rgba(
                           vlibc_get_pixel(canvas, ((vlibc_vec2d){i, j}), 0)
                           )
                     )
            )
        );
    }
    Serial.println("");
  }

  vlibc_arduino_serial_deltaTime = millis() - current_ticks;
  if(vlibc_arduino_serial_deltaTime > 0) {
    Serial.print("\nFPS: ");
    Serial.print(1000/vlibc_arduino_serial_deltaTime);
    Serial.println("");
  }
}

#endif