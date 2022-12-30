#pragma once

#include "Core/Core.h"

#include "Scene/Components/BasicComponents.h"
#include "Scene/Components/2DComponents.h"

#include "Camera.h"

namespace Mana {
	class MANA_API Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void DrawQuad(const mat4& transform, SpriteRendererComponent src);
		static void DrawQuad(TransformComponent tc, SpriteRendererComponent src);
	private:
		static void StartBatch();
		static void NextBatch();
		static void Flush();
	};
}
