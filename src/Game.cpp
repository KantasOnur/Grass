#include "Game.h"
#include "Core/Gui.h"
#include <iostream>
std::unique_ptr<Window> Game::window_;
std::unique_ptr<InputManager> Game::inputManager_;

Game::Game()
{
    window_ = std::make_unique<Window>(640, 480);
    inputManager_ = std::make_unique<InputManager>();
    scene_ = std::make_unique<Scene>(*window_);
    Gui::init(*window_);
}

void Game::run()
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(window_->isOpen())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene_->render();
        EventManager::getInstance().triggerEvent(KeyPressEvent(0, Release));
        window_->update();
    }
    Gui::destroyInstance();
}

