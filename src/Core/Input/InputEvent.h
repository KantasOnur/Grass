#include <iostream>

#include "../Events/Events.h"
#include "../Events/EventHandler.h"

#ifndef INPUTEVENT_H
#define INPUTEVENT_H


class InputEventWrapper
{
public:
    ~InputEventWrapper() = default;
    virtual void triggerKeyEvent(const KeyPressEvent& event) = 0;
    virtual void triggerMouseEvent(const MouseMoveEvent& event) = 0;
};

template<typename SomeKeyEvent, typename SomeMouseEvent>
class InputEvent : public InputEventWrapper
{
public:
    void triggerKeyEvent(const KeyPressEvent& event) override
    {
        EventManager::getInstance().triggerEvent(SomeKeyEvent(event.key_, event.state_));
    }
    void triggerMouseEvent(const MouseMoveEvent &event) override
    {
        EventManager::getInstance().triggerEvent(SomeMouseEvent(event.x_, event.y_));
    }
};

#endif //INPUTEVENT_H
