#pragma once
#include "U8g2lib.h"
#include "utils/appearance.h"
#include "utils/grid.h"

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

    Element(GridPosition gridPos) : gridPos_(gridPos), usingGrid_(true) {}

    virtual ~Element() = default;

    virtual void render(Context *ctx) = 0;

    virtual uint8_t getWidth(Context *ctx) = 0;
    virtual uint8_t getHeight(Context *ctx) = 0;

    void setCoords(int x, int y);
    void setGridPos(GridPosition gridPos);
    void setAppearance(Appearance visuals);

    int getX(void) const { return x_; }
    int getY(void) const { return y_; }

    void layout(Context *ctx);

    virtual bool isInteractive() const = 0;
    /* virtual void onClick() = 0;
    virtual void onFocusChange(bool gainedFocus) = 0; */

  protected:
    bool usingGrid_;
    GridPosition gridPos_;
    Appearance visuals_;

    int x_, y_;
    void drawBorder(Context *ctx);
  };
}; // namespace UILib
