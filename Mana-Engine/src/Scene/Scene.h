#pragma once

#include "Core/Core.h"
#include "Scene/Entity.h"

#include <entt/entt.hpp>

namespace Mana {
	class MANA_API Scene {
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
	private:
		entt::registry registry;
	};
}
