#include "manapch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Mana {
	void OpenGLRenderAPI::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			MANA_CORE_ERROR("Failed to initialize OpenGL context");
			return;
		}

		const char* renderer = (const char*)glGetString(GL_RENDERER);
		const char* version = (const char*)glGetString(GL_VERSION);
		const char* glslVersion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		MANA_CORE_INFO("Renderer       : {0}", renderer);
		MANA_CORE_INFO("OpenGL Version : {0}", version);
		MANA_CORE_INFO("GLSL Version   : {0}", glslVersion);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRenderAPI::SetClearColor(vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.w);
	}
}
