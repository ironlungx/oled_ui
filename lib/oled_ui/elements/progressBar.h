#pragma once

#include "element.h"
namespace UILib {

  class ProgressBar : public Element {
  public:
    // Constructor for absolute pixel positioning and size
    ProgressBar(int x, int y, int initialProgress, int w, int h, int maxProgress = 100)
        : Element(x, y), progress(initialProgress), maxWidth_(w), maxHeight_(h), maxProgress_(maxProgress), gridSpanW_(0),
          gridSpanH_(0) // Not using grid span
    {}

    // Constructor for grid positioning and grid-based size (span)
    ProgressBar(GridPosition gridPos, int initialProgress, int gridSpanW, int gridSpanH, int maxProgress = 100)
        : Element(gridPos), progress(initialProgress), maxWidth_(0), maxHeight_(0), // Will be calculated in layout
          maxProgress_(maxProgress), gridSpanW_(gridSpanW), gridSpanH_(gridSpanH)   // Store grid span
    {}

    // Override layout to calculate size from grid span
    void layout(Context *ctx);

    void render(Context *ctx) override;

    void setProgress(int progress);
    int getProgress() const { return progress; }

    void operator+=(int rhs) { setProgress(progress + rhs); }
    void operator-=(int rhs) { setProgress(progress - rhs); }

    uint8_t getWidth(Context *ctx) override { return maxWidth_; }
    uint8_t getHeight(Context *ctx) override { return maxHeight_; }

    bool isInteractive() const override { return false; };

  private:
    int progress;
    int maxWidth_;  // Actual pixel width (calculated in layout if using grid)
    int maxHeight_; // Actual pixel height (calculated in layout if using grid)
    int maxProgress_;
    int gridSpanW_; // Desired width in grid cells (if using grid)
    int gridSpanH_; // Desired height in grid cells (if using grid)
  };
}; // namespace UILib
