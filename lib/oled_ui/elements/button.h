#pragma once
#include "element.h"
#include <functional>

namespace UILib {
  using ButtonCallback = std::function<void(void *, uint8_t)>; // Function can have some parameters, and uint8_t
                                                               // to show what the action was

  struct ButtonSpec {
    bool isToggleable;
    ButtonCallback onHover; // Change the uint8_t parameter to show if it gained hover and lost hover
    ButtonCallback onClick;
  };

  class Button : public Element {
  private:
    bool isPressed_;
    ButtonSpec *spec_;
  public:
    Button(int x, int y, ButtonSpec *spec);
  };

  template <size_t N> class TextButton : public Element {
  private:
  };
}; // namespace UILib
