#pragma once

#include "Core/Core.h"

#include <entt/entt.hpp>

namespace Mana {
	class Scene;

	class MANA_API Entity
	{
	public:
		template <typename T>
		T& getComponent()
		{
			return registry.get<T>(handle);
		}

		template <typename T>
		bool hasComponent()
		{
			return registry.has<T>(handle);
		}

		template <typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			return registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template <typename T>
		void removeComponent()
		{
			registry.remove<T>(handle);
		}

	private:
		Entity(entt::entity handle, entt::registry& registry)
			: handle(handle), registry(registry)
		{
		}

	private:
		entt::entity handle;
		entt::registry& registry;
		
		friend class Scene;
	};
}
