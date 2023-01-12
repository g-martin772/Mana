#pragma once

#include "Core/Core.h"
#include "VulkanPipeline.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	class MANA_API VulkanFrameBuffer {
	public:
		void Init();
		void Clean();

		void RecordCommandBuffer(uint32_t imageIndex, uint32_t frame, const Ref<VulkanPipeline>& pipeline);

		inline const uint32_t GetFramesOnFlight() { return 2; }

		inline const std::vector<VkFramebuffer>& GetBuffers() const { return m_Framebuffers; }
		inline const std::vector<VkSemaphore>& GetImageAvailableSemaphores() const { return m_ImageAvailableSemaphores; }
		inline const std::vector<VkSemaphore>& GetRenderFinishedSemaphores() const { return m_RenderFinishedSemaphores; }
		inline const std::vector<VkFence>& GetInFlightFences() const { return m_InFlightFences; }
		inline VkCommandPool GetCommandPool() const { return m_CommandPool; }
		inline std::vector<VkCommandBuffer> GetCommandBuffers() const { return m_CommandBuffers; }
	private:
		void CreateSyncObjects();
	private:
		std::vector<VkFramebuffer> m_Framebuffers;
		std::vector<VkSemaphore> m_ImageAvailableSemaphores;
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;
		std::vector<VkFence> m_InFlightFences;

		VkCommandPool m_CommandPool;
		std::vector<VkCommandBuffer> m_CommandBuffers;
	};
}
