// Credits to TheCherno for the great Buffer API

#include "manapch.h"
#include "Buffer.h"

#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mana {
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(size);
		}

		MANA_CORE_ERROR("Invalid Render API");
		__debugbreak();
		return nullptr;
    }

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		MANA_CORE_ERROR("Invalid Render API");
		__debugbreak();
		return nullptr;
	}
	
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		MANA_CORE_ERROR("Invalid Render API");
		__debugbreak();
		return nullptr;
	}

	Ref<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		MANA_CORE_ERROR("Invalid Render API");
		__debugbreak();
		return nullptr;
	}
	
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			MANA_CORE_ERROR("No Render API Selected");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLUniformBuffer>(size, binding);
		}

		MANA_CORE_ERROR("Invalid Render API");
		__debugbreak();
		return nullptr;
	}
}
