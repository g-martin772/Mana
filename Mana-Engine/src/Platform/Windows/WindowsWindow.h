#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"

namespace Mana {
	class MANA_API WindowsWindow : public Window {
	public:
		WindowsWindow() { Init(); }
		~WindowsWindow() { Shutdown(); }

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void OnUpdate() override;
		virtual void OnEvent() override;
	private:
		GLFWwindow* m_Window;
	};
}