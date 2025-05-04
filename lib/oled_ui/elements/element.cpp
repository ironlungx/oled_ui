#include "element.h"
#include "oled_ui.h"

namespace UILib {
  void Element::drawBorder(Context *ctx) {
    if (visuals_.borderSize <= 0)
      return;

    int length = getWidth(ctx);
    int height = getHeight(ctx);

    int x1 = x_ - visuals_.paddingLeft;
    int y1 = y_ - visuals_.paddingTop;
    int x2 = x1 + visuals_.paddingLeft + length + visuals_.paddingRight - 1;
    int y2 = y1 + visuals_.paddingTop + height + visuals_.paddingBottom - 1;

    switch (visuals_.borderType) {
      case Appearance::BorderType::SOLID:
        ctx->u8g2->drawFrame(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
        break;
      case Appearance::BorderType::DOTTED:
        for (int i = 0; i < visuals_.borderSize; ++i) {
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
        for (int i = 0; i < visuals_.borderSize; ++i) {
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

  void Element::setCoords(int x, int y) {
    x_ = x;
    y_ = y;
    usingGrid_ = false;
  }

  void Element::setGridPos(GridPosition pos) {
    gridPos_ = pos;
    usingGrid_ = true;
  }

  void Element::setAppearance(Appearance visuals) { visuals_ = visuals; }

  void Element::render(Context *ctx) {
    drawBorder(ctx);
    if (usingGrid_ && ctx && ctx->grid) {
      uint8_t anchorX = ctx->grid->getVerticalLinePosition(gridPos_.gridX);
      uint8_t anchorY = ctx->grid->getHorizontalLinePosition(gridPos_.gridY);

      ctx->u8g2->drawDisc(anchorX, anchorY, 1);
    }
  }

  void Element::layout(Context *ctx) {
    if (!usingGrid_)
      return;

    uint8_t initialX = ctx->grid->getVerticalLinePosition(gridPos_.gridX);
    uint8_t initialY = ctx->grid->getHorizontalLinePosition(gridPos_.gridY);

    uint8_t width = getWidth(ctx);
    uint8_t height = getHeight(ctx);

    switch (gridPos_.anchorFrom) {
      case AnchorPoint::TOP_LEFT:
        x_ = initialX;
        y_ = initialY;
        break;
      case AnchorPoint::TOP_CENTER:
        x_ = initialX - (width / 2);
        y_ = initialY;
        break;
      case AnchorPoint::TOP_RIGHT:
        x_ = initialX - width;
        y_ = initialY;
        break;

      case AnchorPoint::CENTER_LEFT:
        x_ = initialX;
        y_ = initialY - (height / 2);
        break;
      case AnchorPoint::CENTER:
        x_ = initialX - (width / 2);
        y_ = initialY - (height / 2);
        break;
      case AnchorPoint::CENTER_RIGHT:
        x_ = initialX - width;
        y_ = initialY - (height / 2);
        break;

      case AnchorPoint::BOTTOM_LEFT:
        x_ = initialX;
        y_ = initialY - height;
        break;
      case AnchorPoint::BOTTOM_CENTER:
        x_ = initialX - (width / 2);
        y_ = initialY - height;
        break;
      case AnchorPoint::BOTTOM_RIGHT:
        x_ = initialX - width;
        y_ = initialY - height;
        break;
      default:
        x_ = initialX;
        y_ = initialY;
        break;
    }
  }
}; // namespace UILib
