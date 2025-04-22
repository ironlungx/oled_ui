#include "oled_ui.h"

namespace UILib {
  void Element::drawBorder(Context *ctx, Appearance *visuals) {
    if (!visuals || visuals->borderSize <= 0)
      return;

    int length = getLength(ctx);
    int height = getHeight(ctx);

    int x1 = x_ - visuals->paddingLeft;
    int y1 = y_ - visuals->paddingTop;
    int x2 = x1 + visuals->paddingLeft + length + visuals->paddingRight - 1;
    int y2 = y1 + visuals->paddingTop + height + visuals->paddingBottom - 1;

    switch (visuals->borderType) {
      case Appearance::BorderType::SOLID:
        ctx->u8g2->drawFrame(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
        break;
      case Appearance::BorderType::DOTTED:
        for (int i = 0; i < visuals->borderSize; ++i) {
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y1 + i, x2 - i, y1 + i,
                         2); // Top
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y2 - i, x2 - i, y2 - i,
                         2); // Bottom
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y1 + 1 + i, x1 + i, y2 - 1 - i,
                         2); // Left
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x2 - i, y1 + 1 + i, x2 - i, y2 - 1 - i,
                         2); // Right
        }
        break;
      case Appearance::BorderType::DASHED:
        int dashFactor = 4; // Adjust for dash length and spacing
        for (int i = 0; i < visuals->borderSize; ++i) {
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y1 + i, x2 - i, y1 + i,
                         dashFactor); // Top
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y2 - i, x2 - i, y2 - i,
                         dashFactor); // Bottom
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x1 + i, y1 + 1 + i, x1 + i, y2 - 1 - i,
                         dashFactor); // Left
          u8g2_DrawDLine(ctx->u8g2->getU8g2(), x2 - i, y1 + 1 + i, x2 - i, y2 - 1 - i,
                         dashFactor); // Right
        }
        break;
    }
  }

  long map(long x, long in_min, long in_max, long out_min, long out_max) { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

  void ProgressBar::render(UILib::Context *ctx, Appearance *visuals) {
    int barWidth = map(progress, 0, maxProgress_, 0, maxWidth_);

    ctx->u8g2->drawFrame(x_, y_, maxWidth_, maxHeight_);
    ctx->u8g2->drawBox(x_ + 1, y_ + 1, barWidth - 2, maxHeight_ - 2);
    drawBorder(ctx, visuals);
  }

  void ProgressBar::setProgress(int progress) {
    if (progress >= 0 && progress <= maxProgress_) {
      this->progress = progress;
    }
  }

  void u8g2_DrawDLine(u8g2_t *u8g2, u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2, u8g2_int_t d) {
    // https://github.com/olikraus/u8glib/issues/337#issuecomment-657539929
    u8g2_uint_t tmp;
    u8g2_uint_t x, y;
    u8g2_uint_t dx, dy;
    u8g2_int_t err;
    u8g2_int_t ystep;

    uint8_t swapxy = 0;

    /* no intersection check at the moment, should be added... */

    if (x1 > x2)
      dx = x1 - x2;
    else
      dx = x2 - x1;
    if (y1 > y2)
      dy = y1 - y2;
    else
      dy = y2 - y1;

    if (dy > dx) {
      swapxy = 1;
      tmp = dx;
      dx = dy;
      dy = tmp;
      tmp = x1;
      x1 = y1;
      y1 = tmp;
      tmp = x2;
      x2 = y2;
      y2 = tmp;
    }
    if (x1 > x2) {
      tmp = x1;
      x1 = x2;
      x2 = tmp;
      tmp = y1;
      y1 = y2;
      y2 = tmp;
    }
    err = dx >> 1;
    if (y2 > y1)
      ystep = 1;
    else
      ystep = -1;
    y = y1;

#ifndef U8G2_16BIT
    if (x2 == 255)
      x2--;
#else
    if (x2 == 0xffff)
      x2--;
#endif

    for (x = x1; x <= x2; x++) {
      if (swapxy == 0) {
        if (d == 0) {
          /* solid line */
          u8g2_DrawPixel(u8g2, x, y);
        } else if (d == 1) {
          /* dotted line */
          if (x % 2 == 0)
            u8g2_DrawPixel(u8g2, x, y);
        } else if (d > 1) {
          /* dashed line */
          if ((x / d) % 2 == 0)
            u8g2_DrawPixel(u8g2, x, y);
        } else if (d < 0) {
          /* dashed line inverted */
          if ((x / -d) % 2 != 0)
            u8g2_DrawPixel(u8g2, x, y);
        }
      } else {
        if (d == 0) {
          /* solid line */
          u8g2_DrawPixel(u8g2, y, x);
        } else if (d == 1) {
          /* dotted line */
          if (x % 2 == 0)
            u8g2_DrawPixel(u8g2, y, x);
        } else if (d > 1) {
          /* dashed line */
          if ((x / d) % 2 == 0)
            u8g2_DrawPixel(u8g2, y, x);
        } else if (d < 0) {
          /* dashed line inverted */
          if ((x / -d) % 2 != 0)
            u8g2_DrawPixel(u8g2, y, x);
        }
      }
      err -= (uint8_t)dy;
      if (err < 0) {
        y += (u8g2_uint_t)ystep;
        err += (u8g2_uint_t)dx;
      }
    }
  }
} // namespace UILib
