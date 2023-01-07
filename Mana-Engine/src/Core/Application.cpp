#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"
#include "Math/Math.h"

#include "Scene/Scene.h"
#include "Scene/Components/BasicComponents.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"

namespace Mana {
	ManaApplication* ManaApplication::s_Instance = nullptr;

	ManaApplication::ManaApplication()
	{
		s_Instance = this;

		m_Window = Window::Create("Mana-Engine", 1280, 720);
		m_LayerStack = std::make_shared<LayerStack>();
	}

	ManaApplication::~ManaApplication()
	{
	}

	void ManaApplication::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			m_LayerStack->OnUpdate();
		}
	}

	bool ManaApplication::OnEvent(Event& e)
	{
		if (e.GetEventType() == EventType::WindowClose) {
			m_Running = false;
			m_Window->Shutdown();
		}

		return m_LayerStack->OnEvent(e);
	}
}
