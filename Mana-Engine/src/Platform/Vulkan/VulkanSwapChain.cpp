#include "manapch.h"
#include "VulkanSwapChain.h"

#include "VulkanRenderAPI.h"

namespace Mana {
	void VulkanSwapChain::Init()
	{
		CreateSwapChain();
		CreateImageViews();
	}



	void VulkanSwapChain::InitSurface(GLFWwindow* window)
	{
		m_Window = window;
		if (glfwCreateWindowSurface(VulkanRenderAPI::GetInstance(), window, nullptr, &m_Surface) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create window surface!");
		}
	}

	void VulkanSwapChain::CleanSurface() {
		vkDestroySurfaceKHR(VulkanRenderAPI::GetInstance(), m_Surface, nullptr);
	}

	




	

	

	void VulkanSwapChain::Clean()
	{
		CleanImages();
		CleanSwapchain();
		CleanSurface();
	}




	void VulkanSwapChain::RecreateSwapchain()
	{
		auto device = VulkanRenderAPI::GetDevice();

		vkDeviceWaitIdle(device->GetDevice());

		VulkanRenderAPI::GetCurrentFrameBuffer()->Clean();
		CleanImages();
		CleanSwapchain();

		CreateSwapChain();
		CreateImageViews();
		VulkanRenderAPI::GetCurrentFrameBuffer()->Init();
	}





	SwapChainSupportDetails VulkanSwapChain::QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.Capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.Formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.Formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.PresentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.PresentModes.data());
		}

		return details;
	}

	QueueFamilys FindQueueFamilies(VkSurfaceKHR surface, VkPhysicalDevice device);





	void VulkanSwapChain::CreateSwapChain()
	{
		auto device = VulkanRenderAPI::GetDevice();

		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device->GetPhysicalDevice()->GetDevice(), m_Surface);

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.Formats);
		VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.PresentModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.Capabilities);

		uint32_t imageCount = swapChainSupport.Capabilities.minImageCount + 1;

		if (swapChainSupport.Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.Capabilities.maxImageCount) {
			imageCount = swapChainSupport.Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_Surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilys indices = FindQueueFamilies(m_Surface, device->GetPhysicalDevice()->GetDevice());
		uint32_t queueFamilyIndices[] = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

		if (indices.GraphicsFamily != indices.PresentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.Capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE; // Required for recreating

		if (vkCreateSwapchainKHR(device->GetDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(device->GetDevice(), m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device->GetDevice(), m_SwapChain, &imageCount, m_SwapChainImages.data());

		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}

	void VulkanSwapChain::CleanSwapchain() {
		auto device = VulkanRenderAPI::GetDevice();

		vkDestroySwapchainKHR(device->GetDevice(), m_SwapChain, nullptr);
	}






	void VulkanSwapChain::CreateImageViews()
	{
		auto device = VulkanRenderAPI::GetDevice();

		m_SwapChainImageViews.resize(m_SwapChainImages.size());

		for (size_t i = 0; i < m_SwapChainImages.size(); i++) {
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_SwapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_SwapChainImageFormat;
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(device->GetDevice(), &createInfo, nullptr, &m_SwapChainImageViews[i]) != VK_SUCCESS) {
				MANA_CORE_ASSERT(false, "Failed to create image views!");
			}
		}
	}

	void VulkanSwapChain::CleanImages()
	{
		auto device = VulkanRenderAPI::GetDevice();

		for (auto imageView : m_SwapChainImageViews) {
			vkDestroyImageView(device->GetDevice(), imageView, nullptr);
		}
	}






	VkSurfaceFormatKHR VulkanSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}

		MANA_CORE_WARN("Ideal swapchain format not available!");
		// Check for second best and so on if ideal format is not available
		return availableFormats[0];
	}

	VkPresentModeKHR VulkanSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}
		else {
			int width, height;
			glfwGetFramebufferSize(m_Window, &width, &height);

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}
}
