#include "manapch.h"
#include "Scene.h"

#include "Components/BasicComponents.h"

#include <entt/entt.hpp>

namespace Mana {
	Entity Scene::CreateEntity() {
		Entity entity(registry.create(), registry);
		entity.addComponent<IDComponent>();
		entity.addComponent<TagComponent>();
		entity.addComponent<TransformComponent>();
		return entity;
	}

	void Scene::DestroyEntity(Entity entity) {
		registry.destroy(entity.handle);
	}
}
