#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Mana {
	struct MANA_API IDComponent {
		IDComponent() = default;
		IDComponent(IDComponent&) = default;
		IDComponent(uint64_t id) { ID = id; }

		uint64_t ID = 1234567890; // TODO: UUID System
	};

	struct MANA_API TagComponent {
		TagComponent() = default;
		TagComponent(TagComponent&) = default;
		TagComponent(const char* name) { Name = name; }

		const char* Name = "Default-Entity";
	};

	struct MANA_API TransformComponent {
		TransformComponent() = default;
		TransformComponent(TransformComponent&) = default;

		TransformComponent(const vec3& position, const vec3& scale = { 0.0f, 0.0f, 0.0f }, const vec3& rotation = { 0.0f, 0.0f, 0.0f })
			: Position(position), Scale(scale), Rotation(rotation) {  }

		vec3 Position = { 0.0f, 0.0f, 0.0f };
		vec3 Scale = { 0.0f, 0.0f, 0.0f };
		vec3 Rotation = { 0.0f, 0.0f, 0.0f };

		mat4 GetTransform() {
			return translate(mat4(1.0f), Position)
				 * toMat4(glm::quat(Rotation))
				 * scale(mat4(1.0f), Scale);
		}
	};

	// CameraComponent
}
