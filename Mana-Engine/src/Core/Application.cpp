#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"
#include "Math/Math.h"

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
		m_Window = Window::Create("Mana-Engine", 1280, 720);

		Vec2 vec(5.0f, 2.0f);
		vec += Vec2(1, 2);
		Vec3 pos(1.0f, 1.0f, 1.0f);
		Vec4 color(1.0f, 0.0f, 1.0f, 1.0f);

		MANA_CORE_TRACE("x: {0} y: {1}", vec.x, vec.y);
		MANA_CORE_TRACE("x: {0} y: {1} z: {2}", pos.x, pos.y, pos.z);
		MANA_CORE_TRACE("r: {0} g: {1} b: {2} w: {3}", color.r, color.g, color.b, color.w);
	}

	ManaApplication::~ManaApplication()
	{
	}

	void ManaApplication::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}
