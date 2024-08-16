#include "Window.h"
#include "../Game.h"

#include <iostream>
int Window::width_;
int Window::height_;

Window::Window(const int& width, const int& height)
{
    width_ = width;
    height_ = height;

    if(!glfwInit())
    {
        std::cout << "Failed to initialize GLFW." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(width_, height_, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window_);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetWindowSizeCallback(window_, windowResizeCallback);
    glfwSetCursorPosCallback(window_, mouseMoveCallback);

    glfwSwapInterval(0);
}

Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Window::update() const
{
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

double Window::getTime()
{
    return glfwGetTime();
}

float Window::getDeltaTime()
{
    float current = getTime();
    float dt = current - lastTime_;
    lastTime_ = current;
    return dt;
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(window_);
}


void Window::windowResizeCallback(GLFWwindow* window, int width, int height)
{
    width_ = width;
    height_ = height;

    EventManager::getInstance().triggerEvent(WindowResizeEvent(width, height));
}

void Window::mouseMoveCallback(GLFWwindow *window, double xpos, double ypos)
{
    EventManager::getInstance().triggerEvent(MouseMoveEvent(xpos, ypos));
}
