#include "manapch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Mana {
    Ref<Window> Window::Create(const char* name, uint32_t width, uint32_t height)
    {
#ifdef MANA_PLATFORM_WINDOWS
        return std::make_shared<WindowsWindow>(name, width, height);
#else
    #error Mana currently only supports windows
#endif
    }
}

