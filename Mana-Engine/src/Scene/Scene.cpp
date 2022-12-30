#include "manapch.h"
#include "Scene.h"

#include "Components/BasicComponents.h"
#include "Components/2DComponents.h"
#include "Renderer/Renderer2D.h"

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
		Renderer2D::BeginScene(OrthographicCamera(-100, 100, -100, 100));

		auto renderable = m_Registry.view<SpriteRendererComponent, TransformComponent>();
		for (auto entity : renderable) {
			auto& tc = renderable.get<TransformComponent>(entity);
			auto& src = renderable.get<SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(tc, src);
		}

		Renderer2D::EndScene();
	}
}
