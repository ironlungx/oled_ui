#pragma once
#include <cstdint>

using Font = const uint8_t *;

class Appearance {
public:
  enum class BorderType { SOLID, DOTTED, DASHED };

  Appearance(int borderSize, BorderType borderType, uint8_t padding, uint8_t margin) : borderSize(borderSize), borderType(borderType) {
    setPadding(padding);
    setMargin(margin);
  }

  // Constructor with default values
  Appearance(int borderSize = 0, BorderType borderType = BorderType::SOLID, uint8_t paddingLeft = 0, uint8_t paddingRight = 0, uint8_t paddingTop = 0,
             uint8_t paddingBottom = 0, uint8_t marginLeft = 0, uint8_t marginRight = 0, uint8_t marginTop = 0, uint8_t marginBottom = 0)

      : borderSize(borderSize), borderType(borderType), paddingLeft(paddingLeft), paddingRight(paddingRight), paddingTop(paddingTop),
        paddingBottom(paddingBottom), marginLeft(marginLeft), marginRight(marginRight), marginTop(marginTop), marginBottom(marginBottom) {}

  int borderSize;
  BorderType borderType;

  uint8_t paddingLeft;
  uint8_t paddingRight;
  uint8_t paddingTop;
  uint8_t paddingBottom;

  void setPadding(uint8_t padding) { paddingLeft = paddingRight = paddingTop = paddingBottom = padding; }

  void setPaddingLeft(uint8_t padding) { paddingLeft = padding; }
  void setPaddingRight(uint8_t padding) { paddingRight = padding; }
  void setPaddingTop(uint8_t padding) { paddingTop = padding; }
  void setPaddingBottom(uint8_t padding) { paddingBottom = padding; }

  uint8_t marginLeft;
  uint8_t marginRight;
  uint8_t marginTop;
  uint8_t marginBottom;

  void setMargin(uint8_t margin) { marginLeft = marginRight = marginTop = marginBottom = margin; }

  void setMarginLeft(uint8_t margin) { marginLeft = margin; }
  void setMarginRight(uint8_t margin) { marginRight = margin; }
  void setMarginTop(uint8_t margin) { marginTop = margin; }
  void setMarginBottom(uint8_t margin) { marginBottom = margin; }
};
