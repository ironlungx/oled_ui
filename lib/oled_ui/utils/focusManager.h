#pragma once

#include "elements/element.h"
#include <functional>
#include <vector>

#define MAX_EVENTS 128

namespace UILib {
  struct InputEvent {
    enum class Type { UP, DOWN, LEFT, RIGHT, SELECT, BACK, POINT, OTHER, NONE };
    Type type;

    // TODO: implement pointing device
    int x;
    int y;
  };

  class Scene {
  private:
    std::vector<Element*> elements_;
    Element *focusedElement_;
    InputEvent eventsQueue[MAX_EVENTS];

    struct {
      InputEvent events[MAX_EVENTS];
      int top;
    } EventStack_;

    // Queue related stuff...
    bool isEventStackEmpty();
    bool isEventStackFull();

    InputEvent popEvent();
    // InputEvent peepEventStack(); // Is it reallllly needed?


  public:
    Scene();

    Scene &addElement(Element *element);
    Scene &removeElement(Element *element);

    void pushEvent(InputEvent e);

    void process();
  };
}; // namespace UILib
