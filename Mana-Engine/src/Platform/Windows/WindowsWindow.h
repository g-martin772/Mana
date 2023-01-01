#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

#define GLFW_INCLUDE_NONE
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

		virtual void* GetNativeWindow() const override { return (void*)m_Window; }

		void Invalidate();
	private:
		void InitVulkan();
		void InitOpenGL();
		void SetCalbacks();
	private:
		GLFWwindow* m_Window;
		const char* m_Name;
		int m_Width;
		int m_Height;
	};
}