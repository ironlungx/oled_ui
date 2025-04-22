#pragma once
#include <U8g2lib.h>
#include <cstring>

#include "appearance.h"

namespace UILib {
  long map(long x, long in_min, long in_max, long out_min, long out_max);

  class Context {
  public:
    Context(U8G2 *u8g2) : u8g2(u8g2) {}
    U8G2 *u8g2;
  };

  class Element {
  public:
    Element(int x, int y) : x_(x), y_(y) {}
    Element() : x_(-1), y_(-1) {}

    virtual ~Element() = default;

    virtual void render(Context *ctx, Appearance *visuals) = 0;

    virtual uint8_t getLength(Context *ctx) = 0;
    virtual uint8_t getHeight(Context *ctx) = 0;

    void setCoords(int x, int y) {
      x_ = x;
      y_ = y;
    }

  protected:
    int x_, y_;
    void drawBorder(Context *ctx, Appearance *visuals);
  };

  class LabelSpec {
  public:
    LabelSpec(Font font) : font(font) {}
    Font font;
  };

  template <size_t MaxSize> class Label : public Element {
  public:
    Label(int x, int y, LabelSpec *spec, const char *initialText = "") : Element(x, y), _spec(spec) {
      strncpy(_text, initialText, MaxSize - 1);
      _text[MaxSize - 1] = '\0';
    }

    Label(const char *initialText = "") : Element() {
      strncpy(_text, initialText, MaxSize - 1);
      _text[MaxSize - 1] = '\0';
    }

    void render(Context *ctx, Appearance *visuals) override {
      if (_spec && _spec->font) {
        ctx->u8g2->setFont(_spec->font);
      } else {
        ctx->u8g2->setFont(u8g2_font_haxrcorp4089_tr); // Fallback
      }
      ctx->u8g2->drawStr(x_, y_, _text);
      drawBorder(ctx, visuals);
    }

    void setText(const char *newText) {
      strncpy(_text, newText, MaxSize - 1);
      _text[MaxSize - 1] = '\0';
    }

    uint8_t getLength(Context *ctx) override { return ctx->u8g2->getUTF8Width(_text); }

    uint8_t getHeight(Context *ctx) override { return ctx->u8g2->getMaxCharHeight(); }

  private:
    char _text[MaxSize];
    LabelSpec *_spec;
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

    uint8_t getLength(Context *ctx) override { return maxWidth_; }
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
