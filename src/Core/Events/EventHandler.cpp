#include "EventHandler.h"
#include <iostream>

#include <iostream>

void EventManager::sub(std::unique_ptr<EventHandlerWrapperInterface> &&handler)
{
    EventType type = handler->getEventType();
    auto listeners = listeners_.find(type);
    if(listeners != listeners_.end())
    {
        auto& callbacks = listeners->second;
        for(const auto& it : callbacks)
        {
            if(handler->GetType() == it->GetType())
            {
                std::cout << "Attempted to sub identical callback." << std::endl;
                return;
            }
        }
        callbacks.emplace_back(std::move(handler));
    }
    else
    {
        listeners_[type].emplace_back(std::move(handler));
    }
}

void EventManager::triggerEvent(const Event& event)
{
    EventType type = event.getEventType();
    for(auto& handlers : listeners_[type])
    {
        handlers->Exec(event);
    }
}


