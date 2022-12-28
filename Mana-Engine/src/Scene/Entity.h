#pragma once

#include "Core/Core.h"

#include <entt/entt.hpp>

namespace Mana {
	class Scene;

	class MANA_API Entity
	{
	public:
		template <typename T>
		T& GetComponent() const
		{
			return m_Registry.get<T>(m_EntityHandle);
		}

		/*template <typename T>
		bool HasComponent() const
		{
			return m_Registry.has<T>(m_EntityHandle);
		}*/

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args) const
		{
			return m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent() const
		{
			m_Registry.remove<T>(m_EntityHandle);
		}

	private:
		Entity(entt::entity handle, entt::registry& registry)
			: m_EntityHandle(handle), m_Registry(registry)
		{
		}

	private:
		entt::entity m_EntityHandle;
		entt::registry& m_Registry;
		
		// Instances of the Entity class can only be created by the scene, also containing the ecs registry
		friend class Scene;
	};
}
