#pragma once
#include "elements/element.h"

namespace UILib {
  struct LabelSpec {
    Font font;
  };

  template <size_t MaxSize> class Label : public Element {
  public:
    Label(int x, int y, LabelSpec *spec, const char *initialText = "") : Element(x, y), spec_(spec) {
      strncpy(text_, initialText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    Label(GridPosition gridPos, LabelSpec *spec, const char *initialText = "") : Element(gridPos), spec_(spec) {

      strncpy(text_, initialText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    void render(Context *ctx) {
      layout(ctx);
      if (spec_ && spec_->font) {
        ctx->u8g2->setFont(spec_->font);
      } else {
        ctx->u8g2->setFont(u8g2_font_haxrcorp4089_tr); // Fallback
      }
      ctx->u8g2->drawStr(x_, y_, text_);
      Element::render(ctx);
    }

    void setText(const char *newText) {
      strncpy(text_, newText, MaxSize - 1);
      text_[MaxSize - 1] = '\0';
    }

    uint8_t getWidth(Context *ctx) override {
      ctx->u8g2->setFont(spec_->font);
      return ctx->u8g2->getUTF8Width(text_);
    }
    uint8_t getHeight(Context *ctx) override {

      ctx->u8g2->setFont(spec_->font);
      return ctx->u8g2->getMaxCharHeight();
    }

    bool isInteractive() const { return false; };

  private:
    char text_[MaxSize];
    LabelSpec *spec_;
  };
} // namespace UILib
