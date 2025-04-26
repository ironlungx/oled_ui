#pragma once

#include "U8g2lib.h"
#include "appearance.h"

#include "grid.h"

namespace UILib {
  class Context {
  public:
    Context(U8G2 *u8g2, Grid *grid) : u8g2(u8g2), grid(grid) {}

    U8G2 *u8g2;
    Grid *grid;
  };

  class Element {
  public:
    Element(int x, int y) : x_(x), y_(y), usingGrid_(false) {}

    Element(int gridX, int gridY, GridAlignment hAlign, GridAlignment vAlign)
        : gridX_(gridX), gridY_(gridY), hAlign_(hAlign), vAlign_(vAlign), usingGrid_(true) {}

    virtual ~Element() = default;

    virtual void render(Context *ctx, Appearance *visuals) = 0;

    virtual uint8_t getWidth(Context *ctx) = 0;
    virtual uint8_t getHeight(Context *ctx) = 0;

    void setCoords(int x, int y);
    void setGridPos(int gridX, int gridY, GridAlignment hAlign, GridAlignment vAlign);
    
    int getX(void) const { return x_; }
    int getY(void) const { return y_; }

    void layout(Context *ctx);

  protected:
    bool usingGrid_;
    unsigned int gridX_;
    unsigned int gridY_;
    GridAlignment hAlign_;
    GridAlignment vAlign_;

    int x_, y_;
    void drawBorder(Context *ctx, Appearance *visuals);
  };
}; // namespace UILib
