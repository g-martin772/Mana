#pragma once

#include "Core/Core.h"
#include "RenderAPI.h"

namespace Mana {
	class RenderCommand {
	public:
		static void Init() {
			s_RenderAPI = RenderAPI::Create();
			s_RenderAPI->Init();
		}

		static void SetClearColor(vec4 color) {
			s_RenderAPI->SetClearColor(color);
		}

		static void Clear() {
			s_RenderAPI->Clear();
		}

		static void DrawIndexed() {

		}
	private:
		static Scope<RenderAPI> s_RenderAPI;
	};
}