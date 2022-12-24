#include "manapch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Mana {
    Ref<Window> Window::Create()
    {
#ifdef MANA_PLATFORM_WINDOWS
        return std::make_shared<WindowsWindow>();
#endif
    }
}

