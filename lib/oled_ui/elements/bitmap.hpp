#pragma once
#include "element.h"

namespace UILib {
  class Bitmap : public Element {
  private:
    uint8_t w_;
    uint8_t h_;
    const uint8_t *bitmap_;
    const bool isTransparent_;

  public:
    Bitmap(GridPosition gridPos, uint8_t w, uint8_t h, const uint8_t *bitmap, bool transparent)
        : Element(gridPos), w_(w), h_(h), bitmap_(bitmap), isTransparent_(transparent) {}

    Bitmap(int x, int y, uint8_t w, uint8_t h, const uint8_t *bitmap, bool transparent)
        : Element(x, y), w_(w), h_(h), bitmap_(bitmap), isTransparent_(transparent) {}

    void render(Context *ctx) override {
      layout(ctx);

      if (ctx && ctx->u8g2 && bitmap_) {
        ctx->u8g2->setBitmapMode(isTransparent_);
        ctx->u8g2->drawXBM(x_, y_, w_, h_, bitmap_);
      }
      Element::render(ctx);
    }

    uint8_t getWidth(Context *ctx) override { return w_; }
    uint8_t getHeight(Context *ctx) override { return h_; }

    bool isInteractive() const override { return false; }
  };
}; // namespace UILib
