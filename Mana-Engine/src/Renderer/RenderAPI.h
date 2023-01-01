#pragma once

#include "Core/Core.h"

#include "Buffer.h"

namespace Mana {
	class MANA_API RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL,
			Vulkan
		};
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(vec4 color) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) = 0;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) = 0;

		inline static API GetAPI() { return s_API; }
		static Scope<RenderAPI> Create();
	private:
		// To be defined by client in the future, also support for switching at runtime if even possible
		static API s_API;
	};
}