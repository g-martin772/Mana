#include "manapch.h"
#include "Camera.h"

namespace Mana {
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = (ortho(left, right, bottom, top, -1.0f, 1.0f));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	void OrthographicCamera::RecalculateViewMatrix()
	{
		mat4 transform = translate(mat4(1.0f), m_Position) *
			rotate(mat4(1.0f), radians(m_Rotation), vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
