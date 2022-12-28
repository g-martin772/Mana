#pragma once

#include "Core/Core.h"

#include "Scene/Components/BasicComponents.h"
#include "Scene/Components/2DComponents.h"

namespace Mana {
	class MANA_API Renderer2D {
	public:
		Renderer2D();
		~Renderer2D();

		void DrawQuad(TransformComponent tc, SpriteRendererComponent src);
	private:

	};
}
