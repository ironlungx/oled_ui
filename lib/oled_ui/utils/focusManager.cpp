#include "focusManager.h"
#include "elements/element.h"

namespace UILib {
  Scene::Scene() {
    EventStack_.top = -1; // -1 is empty stack
  }

  Scene &Scene::addElement(Element *element) {
    elements_.push_back(element); // Add element to the vector
    return *this;
  }

  Scene &Scene::removeElement(Element *element) {
    auto it = std::find(elements_.begin(), elements_.end(), element);
    if (it != elements_.end()) {
      elements_.erase(it);
    }
    return *this;
  }

  InputEvent Scene::popEvent() {
    if (isEventStackEmpty()) {
      // Underflow...
      return {
          .type = InputEvent::Type::NONE,
          .x = -1,
          .y = -1,
      };
    }

    InputEvent popped = EventStack_.events[EventStack_.top];
    // decrement top pointer
    EventStack_.top--;
    return popped;
  }

  void Scene::pushEvent(InputEvent e) {
    if (isEventStackFull()) {
      // TODO: do something
      // Stack Overflow
      return;
    }

    EventStack_.top++;                       // Increment top
    EventStack_.events[EventStack_.top] = e; // Add event to the stack
  }

}; // namespace UILib
