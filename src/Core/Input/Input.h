#include "../Window.h"
#include "../Events/Events.h"
#include "string"
#include "InputEvent.h"

#ifndef INPUT_H
#define INPUT_H

class Input
{
private:
    Input() = default;
public:
    static Input& getInstance()
    {
        static Input input;
        return input;
    }

    static bool isPressed(const int& key);

    static inline std::unordered_map<int, State> keyMap =
    {
        {GLFW_KEY_SPACE, Release},
        {GLFW_KEY_APOSTROPHE, Release},
        {GLFW_KEY_COMMA, Release},
        {GLFW_KEY_MINUS, Release},
        {GLFW_KEY_PERIOD, Release},
        {GLFW_KEY_SLASH, Release},
        {GLFW_KEY_0, Release},
        {GLFW_KEY_1, Release},
        {GLFW_KEY_2, Release},
        {GLFW_KEY_3, Release},
        {GLFW_KEY_4, Release},
        {GLFW_KEY_5, Release},
        {GLFW_KEY_6, Release},
        {GLFW_KEY_7, Release},
        {GLFW_KEY_8, Release},
        {GLFW_KEY_9, Release},
        {GLFW_KEY_SEMICOLON, Release},
        {GLFW_KEY_EQUAL, Release},
        {GLFW_KEY_A, Release},
        {GLFW_KEY_B, Release},
        {GLFW_KEY_C, Release},
        {GLFW_KEY_D, Release},
        {GLFW_KEY_E, Release},
        {GLFW_KEY_F, Release},
        {GLFW_KEY_G, Release},
        {GLFW_KEY_H, Release},
        {GLFW_KEY_I, Release},
        {GLFW_KEY_J, Release},
        {GLFW_KEY_K, Release},
        {GLFW_KEY_L, Release},
        {GLFW_KEY_M, Release},
        {GLFW_KEY_N, Release},
        {GLFW_KEY_O, Release},
        {GLFW_KEY_P, Release},
        {GLFW_KEY_Q, Release},
        {GLFW_KEY_R, Release},
        {GLFW_KEY_S, Release},
        {GLFW_KEY_T, Release},
        {GLFW_KEY_U, Release},
        {GLFW_KEY_V, Release},
        {GLFW_KEY_W, Release},
        {GLFW_KEY_X, Release},
        {GLFW_KEY_Y, Release},
        {GLFW_KEY_Z, Release},
        {GLFW_KEY_LEFT_BRACKET, Release},
        {GLFW_KEY_BACKSLASH, Release},
        {GLFW_KEY_RIGHT_BRACKET, Release},
        {GLFW_KEY_GRAVE_ACCENT, Release},
        {GLFW_KEY_WORLD_1, Release},
        {GLFW_KEY_WORLD_2, Release},
        {GLFW_KEY_ESCAPE, Release},
        {GLFW_KEY_ENTER, Release},
        {GLFW_KEY_TAB, Release},
        {GLFW_KEY_BACKSPACE, Release},
        {GLFW_KEY_INSERT, Release},
        {GLFW_KEY_DELETE, Release},
        {GLFW_KEY_RIGHT, Release},
        {GLFW_KEY_LEFT, Release},
        {GLFW_KEY_DOWN, Release},
        {GLFW_KEY_UP, Release},
        {GLFW_KEY_PAGE_UP, Release},
        {GLFW_KEY_PAGE_DOWN, Release},
        {GLFW_KEY_HOME, Release},
        {GLFW_KEY_END, Release},
        {GLFW_KEY_CAPS_LOCK, Release},
        {GLFW_KEY_SCROLL_LOCK, Release},
        {GLFW_KEY_NUM_LOCK, Release},
        {GLFW_KEY_PRINT_SCREEN, Release},
        {GLFW_KEY_PAUSE, Release},
        {GLFW_KEY_F1, Release},
        {GLFW_KEY_F2, Release},
        {GLFW_KEY_F3, Release},
        {GLFW_KEY_F4, Release},
        {GLFW_KEY_F5, Release},
        {GLFW_KEY_F6, Release},
        {GLFW_KEY_F7, Release},
        {GLFW_KEY_F8, Release},
        {GLFW_KEY_F9, Release},
        {GLFW_KEY_F10, Release},
        {GLFW_KEY_F11, Release},
        {GLFW_KEY_F12, Release},
        {GLFW_KEY_F13, Release},
        {GLFW_KEY_F14, Release},
        {GLFW_KEY_F15, Release},
        {GLFW_KEY_F16, Release},
        {GLFW_KEY_LEFT_SHIFT, Release}
    };

};


class InputManager
{
private:
    std::unordered_map<int, State> keyStates_;
    std::unordered_map<std::string, std::unique_ptr<InputEventWrapper>> ModeToInputEvent;
    std::string current_ = "";

    void registerKeyboardInput(const KeyPressEvent& event);
    void registerMouseInput(const MouseMoveEvent& event);

public:
    InputManager();
    void switchModeTo(const std::string& modeName) {if(ModeToInputEvent.find(modeName) != ModeToInputEvent.end())current_ = modeName;}
    void sub(const std::string& modeName, std::unique_ptr<InputEventWrapper>&& inputEvent);
};

#endif //INPUT_H
