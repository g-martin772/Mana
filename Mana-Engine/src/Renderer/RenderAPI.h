#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API RenderAPI {
	public:
		enum class API {
			None = 0,
			OpenGL,
		};
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(vec4 color) = 0;

		inline static API GetAPI() { return s_API; }
		static Scope<RenderAPI> Create();
	private:
		// To be defined by client in the future, also support for switching at runtime if even possible
		static API s_API;
	};
}