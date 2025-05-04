#pragma once
#include <U8g2lib.h>

#define MAP(x, in_min, in_max, out_min, out_max) (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

namespace UILib {
  long map(long x, long in_min, long in_max, long out_min, long out_max);
  void u8g2_DrawDLine(u8g2_t *u8g2, u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2, u8g2_int_t d);
}; // namespace UILib
