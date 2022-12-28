#pragma once

#include "Core/Core.h"

#include "Renderer/RenderAPI.h"

namespace Mana {
	class MANA_API OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(vec4 color) override;
	private:
		
	};
}
