#pragma once
#include <cstdint>

using Font = const uint8_t *;

class Appearance {
public:
  enum class BorderType { SOLID, DOTTED, DASHED };

  Appearance(int borderSize, BorderType borderType, uint8_t padding, uint8_t margin)
      : borderSize(borderSize), borderType(borderType) {
    setPadding(padding);
    setMargin(margin);
  }

  // Constructor with default values
  Appearance(int borderSize = 0, BorderType borderType = BorderType::SOLID, uint8_t paddingLeft = 0, uint8_t paddingRight = 0,
             uint8_t paddingTop = 0, uint8_t paddingBottom = 0, uint8_t marginLeft = 0, uint8_t marginRight = 0,
             uint8_t marginTop = 0, uint8_t marginBottom = 0)

      : borderSize(borderSize), borderType(borderType), paddingLeft(paddingLeft), paddingRight(paddingRight),
        paddingTop(paddingTop), paddingBottom(paddingBottom), marginLeft(marginLeft), marginRight(marginRight),
        marginTop(marginTop), marginBottom(marginBottom) {}

  uint8_t borderSize;
  BorderType borderType;

  Appearance &setBorderSize(uint8_t size) {
    borderSize = size;
    return *this;
  }

  Appearance &setBorderType(BorderType type) {
    borderType = type;
    return *this;
  }

  uint8_t paddingLeft;
  uint8_t paddingRight;
  uint8_t paddingTop;
  uint8_t paddingBottom;


  Appearance &setPadding(uint8_t padding) {
    paddingLeft = paddingRight = paddingTop = paddingBottom = padding;
    return *this;
  }

  Appearance &setPaddingLeft(uint8_t padding) {
    paddingLeft = padding;
    return *this;
  }
  Appearance &setPaddingRight(uint8_t padding) {
    paddingRight = padding;
    return *this;
  }
  Appearance &setPaddingTop(uint8_t padding) {
    paddingTop = padding;
    return *this;
  }
  Appearance &setPaddingBottom(uint8_t padding) {
    paddingBottom = padding;
    return *this;
  }

  uint8_t marginLeft;
  uint8_t marginRight;
  uint8_t marginTop;
  uint8_t marginBottom;

  Appearance &setMargin(uint8_t margin) {
    marginLeft = marginRight = marginTop = marginBottom = margin;
    return *this;
  }

  Appearance &setMarginLeft(uint8_t margin) {
    marginLeft = margin;
    return *this;
  }
  Appearance &setMarginRight(uint8_t margin) {
    marginRight = margin;
    return *this;
  }
  Appearance &setMarginTop(uint8_t margin) {
    marginTop = margin;
    return *this;
  }
  Appearance &setMarginBottom(uint8_t margin) {
    marginBottom = margin;
    return *this;
  }
};
