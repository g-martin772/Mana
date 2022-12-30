#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>

namespace Mana {
	class MANA_API Camera {
	public:
		Camera() = default;
		Camera(const mat4& projection) : m_ViewProjection(projection) {}
		virtual ~Camera() = default;

		const mat4& GetViewProjection() const { return m_ViewProjection; }
	protected:
		mat4 m_ViewProjection = mat4(1.0f);
	};

	class MANA_API OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top) : m_ProjectionMatrix(ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		const vec3& GetPosition() { return m_Position; }
		float GetRotation() { return m_Rotation; }

		void SetPosition(vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		void SetProjection(float left, float right, float bottom, float top);

		const mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
	private:
		mat4 m_ProjectionMatrix;
		mat4 m_ViewMatrix;
		mat4 m_ViewProjectionMatrix;

		vec3 m_Position = vec3({ 0, 0, 0 });
		float m_Rotation = 0.0f;
	};
}
