#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"
#include "Math/Math.h"

#include "Scene/Scene.h"
#include "Scene/Components/BasicComponents.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
		m_Window = Window::Create("Mana-Engine", 1280, 720);
		RenderCommand::Init();
		RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		Renderer2D::Init();
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
