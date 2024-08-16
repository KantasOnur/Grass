#ifndef EVENTS_H
#define EVENTS_H

enum EventType
{
    Base,
    KeyPressed, CameraMoved, GuiKeyPressed,
    MouseMoved, CameraRotated, GuiMouseMoved,
    WindowResized
};

enum State
{
    Release,
    Press,
    Repeat
};


class Event
{
public:
    virtual EventType getEventType() const = 0;
    static EventType getStaticEventType() {return Base;}
    virtual ~Event() = default;
};

class KeyPressEvent : public Event
{
public:
    KeyPressEvent(const int& key, const State& state) : key_(key),state_(state) {}
    ~KeyPressEvent() override = default;
    EventType getEventType() const override {return KeyPressed;}
    static EventType getStaticEventType() {return KeyPressed;}
    int key_;
    State state_;
};

class CameraMoveEvent : public KeyPressEvent
{
public:
    CameraMoveEvent(const int& key, const State& state) : KeyPressEvent(key, state) {}
    ~CameraMoveEvent() override = default;
    EventType getEventType() const override {return CameraMoved;}
    static EventType getStaticEventType() {return CameraMoved;}
};

class GuiKeyEvent final : public KeyPressEvent
{
public:
    GuiKeyEvent(const int& key, const State& state) : KeyPressEvent(key, state) {}
    EventType getEventType() const override {return GuiKeyPressed;}
    static EventType getStaticEventType() {return GuiKeyPressed;}
};

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(const int& x, const int& y) : x_(x), y_(y) {}
    EventType getEventType() const override {return MouseMoved;}
    static EventType getStaticEventType() {return MouseMoved;}

    int x_, y_;
};

class CameraRotateEvent : public MouseMoveEvent
{
public:
    CameraRotateEvent(const int& x, const int& y) : MouseMoveEvent(x, y) {}
    EventType getEventType() const override {return CameraRotated;}
    static EventType getStaticEventType() {return CameraRotated;}
};

class GuiMoseMoveEvent final : public MouseMoveEvent
{
public:
    GuiMoseMoveEvent(const int& x, const int& y) : MouseMoveEvent(x, y) {}
    EventType getEventType() const override {return GuiMouseMoved;}
    static EventType getStaticEventType() {return GuiMouseMoved;}
};

class WindowResizeEvent final: public Event
{
public:
    WindowResizeEvent(const int& width, const int& height) : width_(width), height_(height) {}
    EventType getEventType() const override {return WindowResized;}
    static EventType getStaticEventType() {return WindowResized;}
    int width_, height_;
};
#endif //EVENTS_H
