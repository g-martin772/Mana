#pragma once

#include "Core/Core.h"
#include "Scene/Entity.h"

#include <entt/entt.hpp>

namespace Mana {
	class MANA_API Scene {
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		const entt::registry& GetRegistry() const { return m_Registry; }
	private:
		entt::registry m_Registry;
	};
}
