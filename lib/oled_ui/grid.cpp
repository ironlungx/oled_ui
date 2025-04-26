#include "grid.h"
#include <algorithm>

namespace UILib {
  Grid::Grid(int w, int h, int hLines, int vLines)
      : w_(w), h_(h), hLines_(std::max(1u, static_cast<unsigned int>(hLines))),
        vLines_(std::max(1u, static_cast<unsigned int>(vLines))) {

    hPositions_ = new unsigned int[hLines_];
    vPositions_ = new unsigned int[vLines_];

    calculateGrid();
  }

  Grid::~Grid() {
    delete[] vPositions_;
    delete[] hPositions_;
  }

  void Grid::setContainerSize(unsigned int w, unsigned int h) {
    w_ = w;
    h_ = h;
    calculateGrid();
  }

  unsigned int Grid::getHorizontalLinePosition(unsigned int lineIndex) const {
    if (lineIndex >= 0 && lineIndex < hLines_ && hPositions_) {
      return hPositions_[lineIndex];
    }
    return -1; // invalid
  }

  unsigned int Grid::getVerticalLinePosition(unsigned int lineIndex) const {
    if (lineIndex >= 0 && static_cast<unsigned int>(lineIndex) < vLines_ && vPositions_) {
      return static_cast<int>(vPositions_[lineIndex]);
    }
    return -1; // invalid
  }

  unsigned int Grid::getCellWidth() const {
    if (vLines_ <= 1) {
      return w_; // Full width if there's only one vertical line
    }
    return w_ / (vLines_ - 1);
  }

  unsigned int Grid::getCellHeight() const {
    if (hLines_ <= 1) {
      return h_; // Full height if there's only one horizontal line
    }
    return h_ / (hLines_ - 1);
  }

  void Grid::calculateGrid() {
    int rowStep = getCellHeight(); // (y-direction)
    for (int i = 0; i < hLines_; i++) {
      hPositions_[i] = rowStep * i;
    }

    int colStep = getCellWidth(); // (x-direction)
    for (int i = 0; i < vLines_; i++) {
      vPositions_[i] = colStep * i;
    }
  }
} // namespace UILib
