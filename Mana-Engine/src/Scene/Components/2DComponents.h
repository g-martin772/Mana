#pragma once

#include "Core/Core.h"

namespace Mana {
	struct MANA_API SpriteRendererComponent {
		SpriteRendererComponent() = default;
		SpriteRendererComponent(SpriteRendererComponent&) = default;
		SpriteRendererComponent(vec4 color) { Color = color; }

		vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	// Rigidbody2D
	// BoxCollider2D
	// UI/HUD Components ? maybe
}
