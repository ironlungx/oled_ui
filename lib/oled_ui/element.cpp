#include "element.h"

namespace UILib {
  void Element::setCoords(int x, int y) {
    x_ = x;
    y_ = y;
    usingGrid_ = false;
  }
  void Element::setGridPos(int gridX, int gridY, GridAlignment hAlign, GridAlignment vAlign) {
    gridX_ = gridX;
    gridY_ = gridY; // Corrected this line

    hAlign_ = hAlign;
    vAlign_ = vAlign;

    usingGrid_ = true;
  }
  void Element::layout(Context *ctx) {
    if (!usingGrid_)
      return;

    x_ = ctx->grid->getVerticalLinePosition(gridX_);
    y_ = ctx->grid->getHorizontalLinePosition(gridY_);
  }
}; // namespace UILib
