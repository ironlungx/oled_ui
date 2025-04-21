#pragma once
#include <U8g2lib.h>

namespace UILib {
  long map(long x, long in_min, long in_max, long out_min, long out_max);

  class Context {
  public:
    Context(U8G2 *u8g2, const uint8_t *headerFont, const uint8_t *textFont)
        : u8g2(u8g2), headerFont(headerFont), textFont(textFont) {}

    U8G2 *u8g2;
    const uint8_t *headerFont;
    const uint8_t *textFont;
  };

  class Element {
  public:
    Element(int x, int y) : x_(x), y_(y) {}
    virtual void render(Context *ctx) = 0;
    virtual ~Element() = default; // Ensure base class destructor is virtual

  protected:
    int x_, y_;
  };

  // Template Label class allowing compile-time buffer size definition
  template <size_t MaxSize> class Label : public Element {
  public:
    // Constructor: Initializes buffer and copies initial text safely
    Label(int x, int y, const char *initialText) : Element(x, y) {
      strncpy(textBuffer_, initialText, MaxSize - 1);
      textBuffer_[MaxSize - 1] = '\0'; // Ensure null termination
    }

    // Render method: Draws the text from the internal buffer
    void render(Context *ctx) override {
      // Assuming labels use the standard textFont, adjust if needed
      ctx->u8g2->setFont(ctx->textFont);
      ctx->u8g2->drawStr(x_, y_, textBuffer_);
    }

    // SetText method: Updates the label's text safely
    void setText(const char *newText) {
      strncpy(textBuffer_, newText, MaxSize - 1);
      textBuffer_[MaxSize - 1] = '\0'; // Ensure null termination
    }

    // GetText method: Provides read-only access to the text
    const char *getText() const { return textBuffer_; }

  private:
    char textBuffer_[MaxSize]; // Internal buffer for the string
  };

  class ProgressBar : public Element {
  public:
    ProgressBar(int x, int y, int initialProgress, int w, int h,
                int maxProgress = 100)
        : Element(x, y), progress(initialProgress), maxWidth_(w), maxHeight_(h),
          maxProgress_(maxProgress) {}

    void render(Context *ctx) override;

    void setProgress(int progress);
    int getProgress() const { return progress; }

    void operator+=(int rhs) { setProgress(progress + rhs); }
    void operator-=(int rhs) { setProgress(progress - rhs); }

  private:
    int progress;
    int maxWidth_;
    int maxHeight_;
    int maxProgress_;
  };
}; // namespace UILib
