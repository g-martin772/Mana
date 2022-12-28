// Credits to TheCherno for the great Buffer API

#include "manapch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mana {
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(size);
		}

		MANA_CORE_ERROR("Invalid Render API");
		return nullptr;
    }

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		MANA_CORE_ERROR("Invalid Render API");
		return nullptr;
	}
	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		MANA_CORE_ERROR("Invalid Render API");
		return nullptr;
	}
}
