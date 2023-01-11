#pragma once

#include "Core/Core.h"
#include "RenderAPI.h"

#include <glm/glm.hpp>

namespace Mana {
	class RenderCommand {
	public:
		inline static void Init(void* nativeWindow) {
			RenderAPI::Create();
			RenderAPI::s_RenderAPI->Init(nativeWindow);
		}

		inline static void Shutdown() {
			RenderAPI::s_RenderAPI->Shutdown();
		}

		inline static void SetClearColor(vec4 color) {
			RenderAPI::s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear() {
			RenderAPI::s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
			RenderAPI::s_RenderAPI->DrawIndexed(vertexArray, count);
		}

		inline static void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) {
			RenderAPI::s_RenderAPI->SetViewport(originX, originY, width, height);
		}
	};
}