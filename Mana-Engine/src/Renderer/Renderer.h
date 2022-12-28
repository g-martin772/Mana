#pragma once

#include "Core/Core.h"

namespace Mana {
	enum class RenderAPI {
		None = 0,
		OpenGL,
	};

	class MANA_API Renderer {
	public:
		inline static RenderAPI GetAPI() {
			return RenderAPI::OpenGL; 
			// To be defined by client in the future, also support for switching at runtime if even possible
		}
	};
}
