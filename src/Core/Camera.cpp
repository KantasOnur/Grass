#define GLM_ENABLE_EXPERIMENTAL
#include "Camera.h"
#include <iostream>
#include "../Game.h"
#include <glm/gtx/string_cast.hpp>


Camera::Camera(const Window& window, float fov, glm::vec3 position, glm::vec3 up, glm::vec3 front)
    : fov_(fov), position_(position), up_(up), front_(front), window_(&window)
{
    yaw_ = glm::degrees(atan2(front_.z, front_.x));
    pitch_ = glm::degrees(atan2(front_.y, sqrt(front_.x*front_.x + front_.z*front_.z)));

    EventHandler<CameraMoveEvent> keyHandler = [this](const CameraMoveEvent& event) {this->moveCamera(event);};
    EventHandler<CameraRotateEvent> mouseHandler = [this](const CameraRotateEvent& event) {this->lookAround(event);};
    EventHandler<WindowResizeEvent> windowResizeHandler =  [this](const WindowResizeEvent& event) {this->updateProjectionMatrix();};

    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<CameraMoveEvent>>(keyHandler));
    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<CameraRotateEvent>>(mouseHandler));
    EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<WindowResizeEvent>>(windowResizeHandler));

    Game::inputManager_->sub("Camera", std::make_unique<InputEvent<CameraMoveEvent,CameraRotateEvent>>());

    viewM_ = glm::lookAt(position_,  position_ + front_, up_);
    updateProjectionMatrix();
}


void Camera::moveCamera(const CameraMoveEvent &event)
{

    if(Input::keyMap[GLFW_KEY_ESCAPE] == Press) {Game::inputManager_->switchModeTo("Gui"); return;}


    const float speed = 0.001f;
    right_ = glm::normalize(glm::cross(front_, up_));
    glm::vec3 movement = glm::vec3(0.0f);

    if (Input::keyMap[GLFW_KEY_W] != Release) movement += front_;
    if (Input::keyMap[GLFW_KEY_A] != Release) movement -= right_;
    if (Input::keyMap[GLFW_KEY_S] != Release) movement -= front_;
    if (Input::keyMap[GLFW_KEY_D] != Release) movement += right_;
    if (Input::keyMap[GLFW_KEY_SPACE] != Release) movement += glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::keyMap[GLFW_KEY_LEFT_SHIFT] != Release) movement -= glm::vec3(0.0f, 1.0f, 0.0f);

    if(movement != glm::vec3(0.0f, 0.0f, 0.0f)) position_ += glm::normalize(movement) * speed;
    viewM_ = glm::lookAt(position_,  position_ + front_, up_);
}

void Camera::lookAround(const CameraRotateEvent& event)
{
    params p = window_->getParams();
    glm::vec2 deltaPos = glm::vec2(event.x_, event.y_) - glm::vec2(p.width/2, p.height/2);
    float speed = 0.1f;
    yaw_ += speed * deltaPos.x/2;
    pitch_ -= speed * deltaPos.y/2;

    float maxPitch = 89.0f;
    pitch_ = glm::clamp(pitch_, -maxPitch, maxPitch);
    glm::vec3 front;
    front.x = (cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)));
    front.y = sin(glm::radians(pitch_));
    front.z = (sin(glm::radians(yaw_)) * cos(glm::radians(pitch_)));

    front_ = glm::normalize(front);
    glfwSetCursorPos(window_->getWindow(), p.width/2, p.height/2);
    glfwSetInputMode(window_->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

}

void Camera::updateProjectionMatrix()
{
    projM_ = glm::perspective(fov_, window_->getAspectRatio(), 0.1f, 100.0f);
}