#include "manapch.h"
#include "Scene.h"

#include "Components/BasicComponents.h"

#include <entt/entt.hpp>

namespace Mana {
	Entity Scene::CreateEntity() {
		Entity entity(m_Registry.create(), m_Registry);
		entity.AddComponent<IDComponent>();
		entity.AddComponent<TagComponent>();
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity) {
		m_Registry.destroy(entity.m_EntityHandle);
	}

	void Scene::OnUpdate()
	{
		MANA_CORE_TRACE("Updated Scene");
	}
}
