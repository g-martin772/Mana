#include "manapch.h"
#include "RenderAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRenderAPI.h"
#include "Renderer/RenderCommand.h"

namespace Mana {
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::Vulkan;
    Scope<RenderAPI> RenderAPI::s_RenderAPI;

    void RenderAPI::Create()
    {
        switch (s_API)
        {
        case API::None:
            MANA_CORE_ERROR("No Render API Selected");
            s_RenderAPI = nullptr;
            return;
        case API::OpenGL:
            s_RenderAPI = std::make_unique<OpenGLRenderAPI>();
            return;
        case API::Vulkan:
            s_RenderAPI = std::make_unique<VulkanRenderAPI>();
            return;
        }

        MANA_CORE_ASSERT(false, "Invalid Render API");
    }
}
