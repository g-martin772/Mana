#pragma once

#include "Core/Core.h"
#include "VulkanSwapchain.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	class MANA_API VulkanPipeline;

	class MANA_API VulkanFrameBuffer {
	public:
		void Init(const Ref<VulkanSwapChain>& swapchain, const Ref<VulkanPipeline>& renderPipeline);
		void Clean();

		const std::vector<VkFramebuffer>& GetBuffers() const { return m_Framebuffers; }
	private:
		std::vector<VkFramebuffer> m_Framebuffers;

		Ref<VulkanSwapChain> m_Swapchain;
	};
}
