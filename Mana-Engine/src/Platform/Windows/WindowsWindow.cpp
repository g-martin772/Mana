#include "manapch.h"
#include "WindowsWindow.h"

#include "Renderer/RenderCommand.h"
#include "Core/Events/KeyboardEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Application.h"

namespace Mana {

	// Event Callbacks

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			KeyPressedEvent e(key, action == GLFW_REPEAT);
			ManaApplication::Get()->OnEvent(e);
		}
		else if (action == GLFW_RELEASE) {
			KeyReleasedEvent e(key);
			ManaApplication::Get()->OnEvent(e);
		}
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		MouseMovedEvent e(xpos, ypos);
		ManaApplication::Get()->OnEvent(e);
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS) {
			MouseButtonPressedEvent e(button);
			ManaApplication::Get()->OnEvent(e);
		}
		else if(action == GLFW_RELEASE) {
			MouseButtonReleasedEvent e(button);
			ManaApplication::Get()->OnEvent(e);
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		MouseScrolledEvent e(xoffset, yoffset);
		ManaApplication::Get()->OnEvent(e);
	}

	void drop_callback(GLFWwindow* window, int count, const char** paths)
	{
		std::vector<const char*> pathsVector;
		for (int i = 0; i < count; i++)
			pathsVector.push_back(paths[i]);
		FileDroppedEvent e(pathsVector);
		ManaApplication::Get()->OnEvent(e);
	}

	void cursor_enter_callback(GLFWwindow* window, int entered)
	{
		if (entered)
		{
			MouseEnteredEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
		else
		{
			MouseLeftEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
	}

	void window_close_callback(GLFWwindow* window)
	{
		WindowCloseEvent e;
		ManaApplication::Get()->OnEvent(e);
	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		WindowResizeEvent e(width, height);
		ManaApplication::Get()->OnEvent(e);
	}

	void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
	{
		WindowMovedEvent e(xpos, ypos);
		ManaApplication::Get()->OnEvent(e);
	}

	void window_iconify_callback(GLFWwindow* window, int iconified)
	{
		if (iconified)
		{
			WindowMinimizedEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
		else
		{
			WindowRestoredEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
	}

	void window_maximize_callback(GLFWwindow* window, int maximized)
	{
		if (maximized)
		{
			WindowMaximizedEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
		else
		{
			WindowRestoredEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
	}

	void window_focus_callback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			WindowFocusdEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
		else
		{
			WindowFocusLostEvent e;
			ManaApplication::Get()->OnEvent(e);
		}
	}

	// Window Implementation

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

		glfwRequestWindowAttention(m_Window);
		glfwMaximizeWindow(m_Window);

		/*glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		glfwSetWindowOpacity(m_Window, 0.96f);*/

		/*GLFWimage images[2];
		images[0] = load_icon("my_icon.png");
		images[1] = load_icon("my_icon_small.png");

		glfwSetWindowIcon(m_Window, 2, images);*/

		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSetDropCallback(m_Window, drop_callback);
		glfwSetCursorEnterCallback(m_Window, cursor_enter_callback);
		glfwSetWindowCloseCallback(m_Window, window_close_callback);
		glfwSetWindowSizeCallback(m_Window, window_size_callback);
		glfwSetWindowPosCallback(m_Window, window_pos_callback);
		glfwSetWindowIconifyCallback(m_Window, window_iconify_callback);
		glfwSetWindowMaximizeCallback(m_Window, window_maximize_callback);
		glfwSetWindowFocusCallback(m_Window, window_focus_callback);
	}

	void WindowsWindow::Shutdown()
	{
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{	
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::OnEvent()
	{
	}
}
