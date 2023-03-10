#pragma once

#include "Core/Core.h"
#include "Core/Window.h"

namespace Mana {
	class MANA_API ManaApplication {
	public:
		ManaApplication();
		~ManaApplication();
		void Run();
	private:
		Ref<Window> m_Window;
		bool m_Running = true;
	};

	ManaApplication* CreateApplication(char** argv, int argc);
}
