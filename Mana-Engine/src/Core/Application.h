#pragma once

#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Layer.h"

namespace Mana {
	class MANA_API ManaApplication {
	public:
		ManaApplication();
		~ManaApplication();
		void Run();
	protected:
		Ref<LayerStack> m_LayerStack;
	private:
		Ref<Window> m_Window;
		bool m_Running = true;
	};

	ManaApplication* CreateApplication(char** argv, int argc);
}
