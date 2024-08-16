#include "Gui.h"
#include "../Game.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>

using namespace ImGui;

Gui::Gui(const Window& window)
{
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO(); (void)io;
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    EventHandler<GuiKeyEvent> guiKeyHandler = [this](const GuiKeyEvent& event) {this->guiKey(event);};
    EventHandler<GuiMoseMoveEvent> guiMouseHandler = [this](const GuiMoseMoveEvent& event) {this->guiMouse(event);};

    //EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<GuiKeyEvent>>(guiKeyHandler));
    //EventManager::getInstance().sub(std::make_unique<EventHandlerWrapper<GuiMoseMoveEvent>>(guiMouseHandler));

    //Game::inputManager_->sub("Gui", std::make_unique<InputEvent<GuiKeyEvent, GuiMoseMoveEvent>>());
}

void Gui::guiKey(const GuiKeyEvent &event)
{
    if (Input::keyMap[GLFW_KEY_ESCAPE] == Press) {Game::inputManager_->switchModeTo("Camera"); inMode_=false; return;}
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
    inMode_ = true;
}

void Gui::guiMouse(const GuiMoseMoveEvent &event)
{
    glfwSetInputMode(Game::window_->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Gui::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();

}

void Gui::destroyInstance()
{

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    DestroyContext();
    delete instance_;
    instance_ = nullptr;
}