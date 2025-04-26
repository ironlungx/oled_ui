#pragma once
#include <U8g2lib.h>
#include <cstring>

#include "appearance.h"
#include "element.h"

namespace UILib {
  long map(long x, long in_min, long in_max, long out_min, long out_max);

  class LabelSpec {
  public:
    LabelSpec(Font font) : font(font) {}
    Font font;
  };

  template <size_t MaxSize> class Label : public Element {
  public:
    Label(int x, int y, LabelSpec *spec, const char *initialText = "") : Element(x, y), spec_(spec) {
      strncpy(text_, initialText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    Label(int gridX, int gridY, GridAlignment hAlign, GridAlignment vAlign, LabelSpec *spec, const char *initialText = "")
        : Element(gridX, gridY, hAlign, vAlign), spec_(spec) {

      strncpy(text_, initialText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    void render(Context *ctx, Appearance *visuals) override {
      layout(ctx);
      if (spec_ && spec_->font) {
        ctx->u8g2->setFont(spec_->font);
      } else {
        ctx->u8g2->setFont(u8g2_font_haxrcorp4089_tr); // Fallback
      }
      ctx->u8g2->drawStr(x_, y_, text_);
      drawBorder(ctx, visuals);
    }

    void setText(const char *newText) {
      strncpy(text_, newText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    uint8_t getWidth(Context *ctx) override { return ctx->u8g2->getUTF8Width(text_); }
    uint8_t getHeight(Context *ctx) override { return ctx->u8g2->getMaxCharHeight(); }

  private:
    char text_[MaxSize];
    LabelSpec *spec_;
  };

  class ProgressBar : public Element {
  public:
    ProgressBar(int x, int y, int initialProgress, int w, int h, int maxProgress = 100)
        : Element(x, y), progress(initialProgress), maxWidth_(w), maxHeight_(h), maxProgress_(maxProgress) {}

    void render(Context *ctx, Appearance *visuals) override;

    void setProgress(int progress);
    int getProgress() const { return progress; }

    void operator+=(int rhs) { setProgress(progress + rhs); }
    void operator-=(int rhs) { setProgress(progress - rhs); }

    uint8_t getWidth(Context *ctx) override { return maxWidth_; }
    uint8_t getHeight(Context *ctx) override { return maxHeight_; }

  private:
    int progress;
    int maxWidth_;
    int maxHeight_;
    int maxProgress_;
  };

  void u8g2_DrawDLine(u8g2_t *u8g2, u8g2_uint_t x1, u8g2_uint_t y1, u8g2_uint_t x2, u8g2_uint_t y2, u8g2_int_t d);

  namespace Layout {};

}; // namespace UILib
