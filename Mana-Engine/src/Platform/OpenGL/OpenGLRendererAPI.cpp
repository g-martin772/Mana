#include "manapch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Mana {
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         MANA_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       MANA_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_LOW:          MANA_CORE_INFO(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: MANA_CORE_TRACE(message); return;
		}

		MANA_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRenderAPI::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			MANA_CORE_ERROR("Failed to initialize OpenGL context");
			return;
		}

		#ifdef MANA_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif

		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);*/

		const char* renderer = (const char*)glGetString(GL_RENDERER);
		const char* version = (const char*)glGetString(GL_VERSION);

		MANA_CORE_INFO("Renderer       : {0}", renderer);
		MANA_CORE_INFO("OpenGL Version : {0}", version);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRenderAPI::SetClearColor(vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.w);
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		vertexArray->Bind();
		count = count ? count : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderAPI::SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height)
	{
		glViewport(originX, originY, width, height);
	}
}
