#include "manapch.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Renderer/RenderCommand.h"

namespace Mana {
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
    Scope<RenderAPI> RenderCommand::s_RenderAPI;

    Scope<RenderAPI> RenderAPI::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None:
            MANA_CORE_ERROR("No Render API Selected");
            return nullptr;
        case RenderAPI::API::OpenGL:
            return std::make_unique<OpenGLRenderAPI>();
        }

        MANA_CORE_ERROR("Invalid Render API");
        __debugbreak();
        return nullptr;
    }
}