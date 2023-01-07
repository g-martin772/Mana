#pragma once

#include "Core/Core.h"
#include "VulkanRenderAPI.h"

namespace Mana {
	struct MANA_API SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR Capabilities;
		std::vector<VkSurfaceFormatKHR> Formats;
		std::vector<VkPresentModeKHR> PresentModes;
	};

	class MANA_API VulkanSwapChain {
	public:
		void Init(Ref<VulkanLogicalDevice> device);
		void InitSurface(GLFWwindow* window);
		void Clean();

		static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

		const VkSurfaceKHR& GetSurface() const { return m_Surface; }
		const Ref<VulkanLogicalDevice>& GetDevice() const { return m_Device; }
	private:
		void CreateSwapChain();
		void CreateImageViews();

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	private:
		VkSurfaceKHR m_Surface;
		GLFWwindow* m_Window;

		Ref<VulkanLogicalDevice> m_Device;

		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
	};
}
