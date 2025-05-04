#include "progressBar.h"
#include "element.h"
#include "oled_ui.h"

namespace UILib {
  void ProgressBar::render(UILib::Context *ctx) {
    layout(ctx);

    // check if dimensions are valid
    if (maxWidth_ <= 0 || maxHeight_ <= 0) {
      return;
    }

    int innerMaxWidth = maxWidth_ - 2;
    if (innerMaxWidth < 0)
      innerMaxWidth = 0;

    int innerBarWidth = map(progress, 0, maxProgress_, 0, innerMaxWidth);

    if (innerBarWidth < 0)
      innerBarWidth = 0;

    // outer frame
    ctx->u8g2->drawFrame(x_, y_, maxWidth_, maxHeight_);

    // filled part
    if (innerBarWidth > 0) {
      int innerHeight = maxHeight_ - 2;
      if (innerHeight < 0)
        innerHeight = 0;

      if (innerHeight > 0) {
        ctx->u8g2->drawBox(x_ + 1, y_ + 1, innerBarWidth, innerHeight);
      }
    }

    Element::render(ctx);
  }

  // Override layout for ProgressBar
  void ProgressBar::layout(Context *ctx) {
    if (usingGrid_ && ctx && ctx->grid && gridSpanW_ > 0 && gridSpanH_ > 0) {
      if (gridPos_.gridX >= 0 && gridPos_.gridX < ctx->grid->getVerticalLines() && gridPos_.gridY >= 0 &&
          gridPos_.gridY < ctx->grid->getHorizontalLines()) {

        // Get the starting anchor point coordinates (needed for base layout later)
        uint8_t startX = ctx->grid->getVerticalLinePosition(gridPos_.gridX);
        uint8_t startY = ctx->grid->getHorizontalLinePosition(gridPos_.gridY);

        // Calculate end grid indices based on span, clamping to grid boundaries
        int endGridX = gridPos_.gridX + gridSpanW_;
        if (endGridX >= ctx->grid->getVerticalLines()) {
          endGridX = ctx->grid->getVerticalLines() - 1; // Clamp to last line index
        }
        int endGridY = gridPos_.gridY + gridSpanH_;
        if (endGridY >= ctx->grid->getHorizontalLines()) {
          endGridY = ctx->grid->getHorizontalLines() - 1; // Clamp to last line index
        }

        // Get the pixel coordinates of the end lines
        uint8_t endX = ctx->grid->getVerticalLinePosition(endGridX);
        uint8_t endY = ctx->grid->getHorizontalLinePosition(endGridY);

        // Calculate width and height based on the difference between start and end grid line positions
        // Note: This calculates the size based on the TOP_LEFT of the starting cell.
        // The anchoring will adjust the final position later in Element::layout.
        maxWidth_ = endX - startX;
        maxHeight_ = endY - startY;

        // Ensure dimensions are not negative
        if (maxWidth_ < 0)
          maxWidth_ = 0;
        if (maxHeight_ < 0)
          maxHeight_ = 0;

      } else {
        // Invalid start grid position, default to zero size
        maxWidth_ = 0;
        maxHeight_ = 0;
      }
    }
    // If not usingGrid_, maxWidth_ and maxHeight_ retain the values
    // set by the pixel-based constructor, which is correct.

    // NOW, call the base class layout. It will use the just-calculated
    // maxWidth_ and maxHeight_ (via getWidth/getHeight) to correctly
    // calculate the final x_, y_ based on the GridPosition and AnchorPoint.
    Element::layout(ctx);

    // No need to recalculate maxWidth_/maxHeight_ here anymore.
  }

  void ProgressBar::setProgress(int progress) {
    // Clamp progress to valid range
    if (progress < 0) {
      this->progress = 0;
    } else if (progress > maxProgress_) {
      this->progress = maxProgress_;
    } else {
      this->progress = progress;
    }
  }
}; // namespace UILib
