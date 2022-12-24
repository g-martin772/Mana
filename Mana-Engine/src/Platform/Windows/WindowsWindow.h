#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"

namespace Mana {
	class MANA_API WindowsWindow : public Window {
	public:
		WindowsWindow(const char* name, uint32_t width, uint32_t height);
		~WindowsWindow();

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void OnUpdate() override;
		virtual void OnEvent() override;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
	private:
		GLFWwindow* m_Window;
		const char* m_Name;
		uint32_t m_Width;
		uint32_t m_Height;
	};
}