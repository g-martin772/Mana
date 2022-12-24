#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API Window {
	public:
		Window() { }
		virtual ~Window() { }

		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent() = 0;

		static Ref<Window> Create();
	};
}