#include "manapch.h"
#include "VulkanFrameBuffer.h"
#include "VulkanPipeline.h"

namespace Mana {
	void VulkanFrameBuffer::Init(const Ref<VulkanSwapChain>& swapchain, const Ref<VulkanPipeline>& renderPipeline)
	{
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

            if (vkCreateFramebuffer(swapchain->GetDevice()->GetDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
                MANA_CORE_ASSERT(false, "Failed to create framebuffer!");
            }
        }
	}
	
	void VulkanFrameBuffer::Clean()
	{
        for (auto framebuffer : m_Framebuffers) {
            vkDestroyFramebuffer(m_Swapchain->GetDevice()->GetDevice(), framebuffer, nullptr);
        }
	}
}
