#pragma once

#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/Layer.h"

#include "Core/Events/Event.h"

namespace Mana {
	class MANA_API ManaApplication {
	public:
		ManaApplication();
		~ManaApplication();
		void Run();
		bool OnEvent(Event& e);

		void* GetNativeWindow() { return m_Window->GetNativeWindow(); }
		std::string GetName() { return m_Name; }

		inline static ManaApplication* Get() { return s_Instance; }
	protected:
		Ref<LayerStack> m_LayerStack;
		Ref<Window> m_Window;
	private:
		std::string m_Name = "Mana-Game";
		static ManaApplication* s_Instance;
		bool m_Running = true;
	};

	ManaApplication* CreateApplication(char** argv, int argc);
}
