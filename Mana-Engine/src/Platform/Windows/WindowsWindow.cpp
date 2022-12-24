#include "manapch.h"
#include "WindowsWindow.h"

namespace Mana {
	WindowsWindow::WindowsWindow(const char* name, uint32_t width, uint32_t height)
		: m_Name(name), m_Width(width), m_Height(height)
	{
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init()
	{
		if (!glfwInit())
			MANA_CORE_ERROR("Failed to initialize GLFW!");

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);

		if (!m_Window) {
			glfwTerminate();
			MANA_CORE_ERROR("Failed to create GLFW Window!");
		}

		glfwMakeContextCurrent(m_Window);
	}

	void WindowsWindow::Shutdown()
	{
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		if (glfwWindowShouldClose(m_Window))
			Shutdown();

		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::OnEvent()
	{
	}
}