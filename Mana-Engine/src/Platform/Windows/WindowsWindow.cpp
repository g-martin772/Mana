#include "manapch.h"
#include "WindowsWindow.h"

namespace Mana {
	void WindowsWindow::Init()
	{
		if (!glfwInit())
			MANA_CORE_ERROR("Failed to initialize GLFW!");

		m_Window = glfwCreateWindow(640, 480, "ManaEngine", NULL, NULL);

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
		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::OnEvent()
	{
	}
}