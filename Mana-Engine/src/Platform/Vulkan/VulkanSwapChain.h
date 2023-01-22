#pragma once

#include "Core/Core.h"

#include "VulkanDevice.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	struct MANA_API SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR Capabilities;
		std::vector<VkSurfaceFormatKHR> Formats;
		std::vector<VkPresentModeKHR> PresentModes;
	};

	class MANA_API VulkanSwapChain {
	public:
		void Init();
		void InitSurface(GLFWwindow* window);
		void Clean();

		void RecreateSwapchain();

		static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

		inline const VkSurfaceKHR& GetSurface() const { return m_Surface; }
		inline const VkSwapchainKHR& GetSwapchain() const { return m_SwapChain; }
		inline const VkExtent2D& GetSwapchainextent() const { return m_SwapChainExtent; }
		inline const VkFormat& GetSwapchainFormat() const { return m_SwapChainImageFormat; }
		inline const std::vector<VkImageView>& GetImageViews() const { return m_SwapChainImageViews; }
	private:
		void CreateSwapChain();
		void CreateImageViews();

		void CleanSwapchain();
		void CleanSurface();
		void CleanImages();

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	private:
		VkSurfaceKHR m_Surface;
		GLFWwindow* m_Window;

		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		std::vector<VkImageView> m_SwapChainImageViews;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;
	};
}
