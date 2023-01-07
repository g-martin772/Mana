#pragma once

#include "Core/Core.h"
#include "Renderer/RenderAPI.h"
#include "Platform/Vulkan/VulkanDevice.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <optional>
#include <set>
#include <limits>
#include <algorithm>

namespace Mana {
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	class MANA_API VulkanRenderAPI : public RenderAPI {
	public:
		virtual void Init(void* nativeWindow) override;
		virtual void Shutdown() override;
		virtual void Clear() override;
		virtual void SetClearColor(vec4 color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) override;
	public:
		static VkInstance GetInstance() { return s_Instance; }
	private:
		void CreateInstance();
		void InitDebugMessanger();
		
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		
		
	private:
		inline static VkInstance s_Instance;

		Ref<VulkanPhysicalDevice> m_PhysicalDevice = std::make_shared<VulkanPhysicalDevice>();
		Ref<VulkanLogicalDevice> m_Device = std::make_shared<VulkanLogicalDevice>();
		Ref<VulkanSwapChain> m_SwapChain = std::make_shared<VulkanSwapChain>();
		
		VkDebugUtilsMessengerEXT m_DebugMessenger;
	};
}
