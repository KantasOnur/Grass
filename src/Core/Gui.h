#ifndef GUI_H
#define GUI_H
#include <stdexcept>
#include "Window.h"
#include "Events/Events.h"


class Gui
{
private:
    explicit Gui(const Window& window);
    void guiKey(const GuiKeyEvent& event);
    void guiMouse(const GuiMoseMoveEvent& event);
    static inline Gui* instance_ = nullptr;
    static bool inline inMode_ = false;
public:
    static void init(const Window& window)
    {
        if(!instance_) instance_ = new Gui(window);
    }
    static Gui& getInstance()
    {
        if(!instance_) {throw std::runtime_error("Gui is not initialized!");}
        return *instance_;
    }
    static void destroyInstance();
    void newFrame();
};



#endif //GUI_H
