#include "Input.h"
#include <iostream>
#include "../../Game.h"

bool Input::isPressed(const int &key)
{
    return glfwGetKey(Game::window_->getWindow(), key);
}


InputManager::InputManager()
{
    EventHandler<KeyPressEvent> keyHandler = [this](const KeyPressEvent& event) {this->registerKeyboardInput(event);};
    EventHandler<MouseMoveEvent> mouseHandler = [this](const MouseMoveEvent& event) {this->registerMouseInput(event);};

    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<KeyPressEvent>>(keyHandler));
    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<MouseMoveEvent>>(mouseHandler));
}

void InputManager::registerKeyboardInput(const KeyPressEvent &event)
{


    if(current_ != "")
    {

        for (auto& it : Input::keyMap)
        {
            if (Input::isPressed(it.first)) {
                if (it.second == Release) {
                    it.second = Press;
                } else {
                    it.second = Repeat;
                }
            } else {
                it.second = Release;
            }
        }
        ModeToInputEvent[current_]->triggerKeyEvent(event);
    }
}

void InputManager::registerMouseInput(const MouseMoveEvent &event)
{
    if(current_ != "")
    {
        ModeToInputEvent[current_]->triggerMouseEvent(event);

    }
}
void InputManager::sub(const std::string& modeName, std::unique_ptr<InputEventWrapper>&& inputEvent)
{
    if(current_ == "")
    {
        ModeToInputEvent[modeName] = std::move(inputEvent);
        current_ = modeName;
    }
    else if(ModeToInputEvent.find(modeName) == ModeToInputEvent.end())
    {
        ModeToInputEvent[modeName] = std::move(inputEvent);
    }
    else
    {
        std::cout << "Mode already exists for " << modeName << std::endl;
    }
}