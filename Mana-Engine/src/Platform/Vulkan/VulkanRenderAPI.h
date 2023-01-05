#pragma once

#include "Core/Core.h"

#include "Renderer/RenderAPI.h"
#include <glm/glm.hpp>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	class MANA_API VulkanRenderAPI : public RenderAPI {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void Clear() override;
		virtual void SetClearColor(vec4 color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) override;
	private:
		void CreateInstance();
		bool CheckValidationLayerSupport();
		void InitDebugMessanger();
		std::vector<const char*> GetRequiredExtensions();
	private:
		VkInstance m_Instance;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
	};
}
