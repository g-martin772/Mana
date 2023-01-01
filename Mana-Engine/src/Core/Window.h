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

		virtual uint32_t GetWidth() const  = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Ref<Window> Create(const char* name = "Mana-Engine", uint32_t width = 720, uint32_t height = 420);
	};
}