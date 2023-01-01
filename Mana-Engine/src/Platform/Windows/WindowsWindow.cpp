#include "manapch.h"
#include "WindowsWindow.h"

#include "Renderer/RenderCommand.h"
#include "Core/Events/KeyboardEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Application.h"
#include "Renderer/RenderAPI.h"

#include "vulkan/vulkan.h"

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

	void WindowsWindow::SetCalbacks() {
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

	void WindowsWindow::Invalidate()
	{
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
	}

	void WindowsWindow::Init()
	{
		if (RenderAPI::GetAPI() == RenderAPI::API::OpenGL)
			InitOpenGL();
		else if (RenderAPI::GetAPI() == RenderAPI::API::Vulkan)
			InitVulkan();
		else
			MANA_CORE_ASSERT(false, "RenderAPI not supported for platform Windows64x");

		SetCalbacks();
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Width, m_Height);
	}

	void WindowsWindow::InitVulkan()
	{
		if (!glfwInit())
			MANA_CORE_ASSERT(false, "Failed to initialize GLFW!");

		if (!glfwVulkanSupported())
			MANA_CORE_ASSERT(false, "Vulkan not supported for this device");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);

		if (!m_Window) {
			glfwTerminate();
			MANA_CORE_ASSERT(false, "Failed to create GLFW Window!");
		}

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

		MANA_CORE_TRACE("{0} Vulkan Instance Extensions found", extensionCount);
		for (const auto& extension : extensions) {
			MANA_CORE_TRACE("\t {0}", extension.extensionName);
		}
		MANA_CORE_TRACE("");
	}

	void WindowsWindow::InitOpenGL()
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
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		RenderCommand::Shutdown();
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
