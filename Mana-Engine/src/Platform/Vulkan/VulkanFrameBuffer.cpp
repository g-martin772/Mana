#include "manapch.h"
#include "VulkanFrameBuffer.h"
#include "VulkanPipeline.h"

#include "VulkanRenderAPI.h"

namespace Mana {
	void VulkanFrameBuffer::Init()
	{
		auto swapchain = VulkanRenderAPI::GetCurrentSwapchain();
		auto renderPipeline = VulkanRenderAPI::GetCurrentPipeline();
		auto device = VulkanRenderAPI::GetDevice();
		// Create Framebuffers

		m_FramebufferResized = false;

		m_Framebuffers.resize(swapchain->GetImageViews().size());

		for (size_t i = 0; i < swapchain->GetImageViews().size(); i++) {
			VkImageView attachments[] = {
				swapchain->GetImageViews()[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPipeline->GetRenderPass();
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapchain->GetSwapchainextent().width;
			framebufferInfo.height = swapchain->GetSwapchainextent().height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(device->GetDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
				MANA_CORE_ASSERT(false, "Failed to create framebuffer!");
			}
		}

		// Create Command Buffers

		QueueFamilys queueFamilyIndices = device->GetPhysicalDevice()->GetQueueFamilys();

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.GraphicsFamily.value();

		if (vkCreateCommandPool(device->GetDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create command pool!");
		}


		m_CommandBuffers.resize(GetFramesOnFlight());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_CommandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

		if (vkAllocateCommandBuffers(device->GetDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to allocate command buffers!");
		}

		CreateSyncObjects();
	}
	
	void VulkanFrameBuffer::Clean()
	{
		auto device = VulkanRenderAPI::GetDevice();

		vkDestroyCommandPool(device->GetDevice(), m_CommandPool, nullptr);
		for (uint32_t i = 0; i < GetFramesOnFlight(); i++) {
			vkDestroySemaphore(device->GetDevice(), m_ImageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(device->GetDevice(), m_RenderFinishedSemaphores[i], nullptr);
			vkDestroyFence(device->GetDevice(), m_InFlightFences[i], nullptr);
		}

		for (auto framebuffer : m_Framebuffers) {
			vkDestroyFramebuffer(device->GetDevice(), framebuffer, nullptr);
		}
	}

	void VulkanFrameBuffer::CreateSyncObjects()
	{
		auto device = VulkanRenderAPI::GetDevice();

		m_ImageAvailableSemaphores.resize(GetFramesOnFlight());
		m_RenderFinishedSemaphores.resize(GetFramesOnFlight());
		m_InFlightFences.resize(GetFramesOnFlight());

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (uint32_t i = 0; i < GetFramesOnFlight(); i++) {
			if (vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(device->GetDevice(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(device->GetDevice(), &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {
				MANA_CORE_ASSERT(false, "Failed to create semaphores!");
			}
		}
	}

	void VulkanFrameBuffer::RecordCommandBuffer(uint32_t imageIndex, uint32_t frame, const Ref<VulkanPipeline>& pipeline) {
		auto swapchain = VulkanRenderAPI::GetCurrentSwapchain();
		
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0;
		beginInfo.pInheritanceInfo = nullptr;

		if (vkBeginCommandBuffer(m_CommandBuffers[frame], &beginInfo) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = pipeline->GetRenderPass();
		renderPassInfo.framebuffer = m_Framebuffers[imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapchain->GetSwapchainextent();
		VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(m_CommandBuffers[frame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(m_CommandBuffers[frame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->GetPipeline());

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapchain->GetSwapchainextent().width);
		viewport.height = static_cast<float>(swapchain->GetSwapchainextent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(m_CommandBuffers[frame], 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapchain->GetSwapchainextent();
		vkCmdSetScissor(m_CommandBuffers[frame], 0, 1, &scissor);

		vkCmdDraw(m_CommandBuffers[frame], 6, 1, 0, 0); // Finally!!!!!!!

		vkCmdEndRenderPass(m_CommandBuffers[frame]);

		if (vkEndCommandBuffer(m_CommandBuffers[frame]) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to record command buffer!");
		}
	}
}
