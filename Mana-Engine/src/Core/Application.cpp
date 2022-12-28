#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"
#include "Math/Math.h"

#include "Scene/Scene.h"
#include "Scene/Components/BasicComponents.h"

#include "Renderer/RenderCommand.h"

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
		m_Window = Window::Create("Mana-Engine", 1280, 720);
		RenderCommand::Init();
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
}
