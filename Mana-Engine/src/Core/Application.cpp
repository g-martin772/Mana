#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"
#include "Math/Math.h"

#include "Scene/Scene.h"
#include "Scene/Components/BasicComponents.h"

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
		m_Window = Window::Create("Mana-Engine", 1280, 720);

		vec2 vec(5.0f, 2.0f);
		vec.set({ 1.0f, 1.0f });
		vec.add({ 0.0f, 0.0f });
		vec += vec;

		MANA_CORE_TRACE("x: {0} y: {1}", vec.x, vec.y);

		Scene scene;

		Entity entity = scene.CreateEntity();
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
