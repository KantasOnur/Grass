#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <functional>
#include "Events.h"
#include <string>

template <typename SomeEvent>
using EventHandler = std::function<void(const SomeEvent& event)>;

class EventHandlerWrapperInterface {
public:
    void Exec(const Event& e)
    {
        Call(e);
    }

    virtual std::string GetType() const = 0;
    virtual EventType getEventType() const = 0;

private:
    virtual void Call(const Event& e) = 0;
};


template <typename SomeEvent>
class EventHandlerWrapper : public EventHandlerWrapperInterface {
public:
    explicit EventHandlerWrapper(const EventHandler<SomeEvent>& handler)
        : handler_(handler), handlerType_(handler.target_type().name()) {};

    EventType getEventType() const override {return SomeEvent::getStaticEventType();}

private:
    void Call(const Event& e) override
    {
        if (e.getEventType() == SomeEvent::getStaticEventType()) {
            handler_(static_cast<const SomeEvent&>(e));
        }
    }

    EventHandler<SomeEvent> handler_;
    const std::string handlerType_;

   std::string GetType() const override { return handlerType_; }


};


class EventManager
{
private:
    std::vector<std::unique_ptr<Event>> queue_;
    std::unordered_map<EventType, std::vector<std::unique_ptr<EventHandlerWrapperInterface>>> listeners_;
    EventManager() = default;

public:
    static EventManager& getInstance()
    {
        static EventManager instance;
        return instance;
    }
    void sub(std::unique_ptr<EventHandlerWrapperInterface>&& handler);
    void triggerEvent(const Event& event);

};
#endif //EVENTHANDLER_H
