#ifndef GAME_H
#define GAME_H
#include <memory>
#include "Scene.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"

class Game
{
private:
    std::unique_ptr<Scene> scene_;
public:
    static std::unique_ptr<Window> window_;
    static std::unique_ptr<InputManager> inputManager_;
    inline static float deltaTime_ = 0.0f;
    Game();
    void run();
};
#endif //GAME_H
