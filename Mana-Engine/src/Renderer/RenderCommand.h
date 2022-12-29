#pragma once

#include "Core/Core.h"
#include "RenderAPI.h"
#include "Math/Vec4.h"

namespace Mana {
	class RenderCommand {
	public:
		inline static void Init() {
			s_RenderAPI = RenderAPI::Create();
			s_RenderAPI->Init();
		}

		inline static void SetClearColor(vec4 color) {
			s_RenderAPI->SetClearColor(color);
		}

		inline static void Clear() {
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
			s_RenderAPI->DrawIndexed(vertexArray, count);
		}

		inline static void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) {
			s_RenderAPI->SetViewport(originX, originY, width, height);
		}
	private:
		static Scope<RenderAPI> s_RenderAPI;
	};
}