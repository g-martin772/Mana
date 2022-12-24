#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
		m_Window = Window::Create();
	}

	ManaApplication::~ManaApplication()
	{
	}

	void ManaApplication::Run()
	{
		MANA_CORE_INFO("SomeText");
		MANA_CORE_TRACE("SomeText");
		MANA_CORE_WARN("SomeText");
		MANA_CORE_ERROR("SomeText");
		while (true)
		{
			m_Window->OnUpdate();
		}
	} 
}
