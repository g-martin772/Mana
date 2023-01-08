#pragma once

#include "Core/Core.h"
#include "VulkanSwapChain.h"
#include "VulkanFrameBuffer.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	class MANA_API VulkanPipeline {
	public:
		void Init(const Ref<VulkanSwapChain>& swapchain);
		void Clean();

		void RecordCommandBuffer(uint32_t imageIndex, const Ref<VulkanFrameBuffer>& framebuffer);

		VkPipelineLayout GetPipelineLayout() const { return m_PipelineLayout; }
		VkRenderPass GetRenderPass() const { return m_RenderPass; }
		VkCommandPool GetCommandPool() const { return m_CommandPool; }
		VkCommandBuffer GetCommandBuffer() const { return m_CommandBuffer; }
	private:
		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_GraphicsPipeline;

		VkRenderPass m_RenderPass;

		VkCommandPool m_CommandPool;
		VkCommandBuffer m_CommandBuffer;

		Ref<VulkanSwapChain> m_Swapchain;
	};
}
