#pragma once

namespace UILib {
  enum class GridAlignment {
    LEFT,          // Horizontal: Left edge aligned to the line
                   // Vertical: Top edge aligned to the line
    CENTER,        // Horizontal: Center aligned to the line
                   // Vertical: Center aligned to the line
    RIGHT,         // Horizontal: Right edge aligned to the line
                   // Vertical: Bottom edge aligned to the line
    TOP = LEFT,    // Alias for clarity in vertical alignment
    BOTTOM = RIGHT // Alias for clarity in vertical alignment
  };

  class Grid {
  private:
    unsigned int hLines_, vLines_; // Number of horizontal and vertical lines
    int w_, h_;                    // Container width and height
    unsigned int *hPositions_;     // Y-positions of horizontal lines
    unsigned int *vPositions_;     // X-positions of vertical lines
    void calculateGrid();          // Calculate grid positions

  public:
    Grid(int w, int h, int hLines, int vLines);
    ~Grid();
    void setContainerSize(unsigned int w, unsigned int h);
    unsigned int getHorizontalLinePosition(unsigned int lineIndex) const;
    unsigned int getVerticalLinePosition(unsigned int lineIndex) const;
    unsigned int getCellWidth() const;
    unsigned int getCellHeight() const;
    unsigned int getHorizontalLines() const { return hLines_; }
    int getVerticalLines() const { return vLines_; }
  };
} // namespace UILib
