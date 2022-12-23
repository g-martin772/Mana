#include "manapch.h"
#include "Application.h"

#include "Core/Log.h"

#include <iostream>

namespace Mana {
	ManaApplication::ManaApplication()
	{
		Log::Init();
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
	}
}
