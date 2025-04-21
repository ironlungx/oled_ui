#include "oled_ui.h"

long UILib::map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void UILib::Label::render(UILib::Context *ctx) {
  ctx->u8g2->setFont(ctx->headerFont);
  ctx->u8g2->setFont(ctx->headerFont);
  ctx->u8g2->drawStr(x_, y_, text);
}

void UILib::ProgressBar::render(UILib::Context *ctx) {
  int barWidth = map(progress, 0, maxProgress_, 0, maxWidth_);
  ctx->u8g2->drawFrame(x_, y_, maxWidth_, maxHeight_);
  ctx->u8g2->drawBox(x_ + 1, y_ + 1, barWidth - 2, maxHeight_ - 2);
}

void UILib::ProgressBar::setProgress(int progress) {
  if (progress >= 0 && progress <= maxProgress_) {
    this->progress = progress;
  }
}
