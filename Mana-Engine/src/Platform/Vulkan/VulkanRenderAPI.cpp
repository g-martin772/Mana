#include "manapch.h"
#include "VulkanRenderAPI.h"

#include "Core/Application.h"

namespace Mana {

#ifdef MANA_DEBUG
	const constexpr bool enableValidationLayers = true;
#else
	const constexpr bool enableValidationLayers = false;
#endif

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	// Debug
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

		switch (messageSeverity)
		{
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			MANA_CORE_TRACE("[Vulkan][ValidationLayer] > {0}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			MANA_CORE_INFO("[Vulkan][ValidationLayer] > {0}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			MANA_CORE_WARN("[Vulkan][ValidationLayer] > {0}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			MANA_CORE_ERROR("[Vulkan][ValidationLayer] > {0}", pCallbackData->pMessage);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
			MANA_CORE_ERROR("[Vulkan][ValidationLayer] > {0}; this should never happen, check validation layers!", pCallbackData->pMessage);
			break;
		}

		return VK_FALSE;
	}

	static constexpr VkDebugUtilsMessengerCreateInfoEXT GetDebugMessangerInfo() {
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = DebugCallback;
		createInfo.pUserData = nullptr;
		return createInfo;
	} // - Debug

	void VulkanRenderAPI::Init(void* nativeWindow)
	{
		m_Window = (GLFWwindow*)nativeWindow;

		CreateInstance();
		InitDebugMessanger();
		CreateSurface();
		PickPhysicalDevice();
		CreateLogicalDevice();
		CreateSwapChain();
	}

	void VulkanRenderAPI::Shutdown()
	{
		vkDestroySwapchainKHR(m_Device, m_SwapChain, nullptr);
		vkDestroyDevice(m_Device, nullptr);

		if (enableValidationLayers) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
			func(m_Instance, m_DebugMessenger, nullptr);
		}

		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanRenderAPI::CreateInstance()
	{
		MANA_CORE_ASSERT(enableValidationLayers && !CheckValidationLayerSupport(), "validation layers requested, but not available!");

		// App Info
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Mana-App";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Mana-Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Instance Info
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		// EnableValidationLayers
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
			auto info = GetDebugMessangerInfo();
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&info;
		}
		else {
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}

		// Extensions
		auto extensions = GetRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		// Create Instance
		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create vulkan instance");
		}

		// Log Extensions
		MANA_CORE_INFO("Vulkan instance created with following extensions: ");

		std::vector<const char*>::iterator it;
		for (it = extensions.begin(); it != extensions.end(); ++it)
			MANA_CORE_INFO("\t{0}", *it);
	}

	bool VulkanRenderAPI::CheckValidationLayerSupport() {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return false;
	}

	void VulkanRenderAPI::InitDebugMessanger()
	{
		if (!enableValidationLayers) return;

		auto info = GetDebugMessangerInfo();

		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
		MANA_CORE_ASSERT(func != nullptr, "Vulkan Debugmessanger Extension not present");

		VkResult result = func(m_Instance, &info, nullptr, &m_DebugMessenger);
		MANA_CORE_ASSERT(result == VK_SUCCESS, "Failed to set up debug messanger");
	}

	void VulkanRenderAPI::CreateSurface()
	{
		if (glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create window surface!");
		}
	}

	void VulkanRenderAPI::PickPhysicalDevice()
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

		MANA_CORE_ASSERT(deviceCount != 0, "No GPU with Vulkan support found!");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

		for (const auto& device : devices) {
			if (IsSuitableDevice(device)) {
				m_PhysicalDevice = device;
				break;
			}
		}

		MANA_CORE_ASSERT(m_PhysicalDevice != VK_NULL_HANDLE, "No suitable GPU found!");

	}

	void VulkanRenderAPI::CreateLogicalDevice()
	{
		QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		VkResult result = vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device);
		MANA_CORE_ASSERT(result == VK_SUCCESS, "Failed to create logical Device!");

		vkGetDeviceQueue(m_Device, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_Device, indices.PresentFamily.value(), 0, &m_PresentQueue);
	}

	void VulkanRenderAPI::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_PhysicalDevice);

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

		QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);
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

		if (vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_Device, m_SwapChain, &imageCount, m_SwapChainImages.data());

		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}

	bool VulkanRenderAPI::IsSuitableDevice(VkPhysicalDevice device)
	{
		// Get device info
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// GetQueueFamilies
		QueueFamilyIndices indices = FindQueueFamilies(device);


		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		bool swapChainAdequate = false;
		if (requiredExtensions.empty()) {
			SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.Formats.empty() && !swapChainSupport.PresentModes.empty();
		}

		return indices.IsComplete() &&
			deviceFeatures.geometryShader &&
			requiredExtensions.empty() &&
			swapChainAdequate;
	}

	std::vector<const char*> VulkanRenderAPI::GetRequiredExtensions() {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	VkSurfaceFormatKHR VulkanRenderAPI::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
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

	VkPresentModeKHR VulkanRenderAPI::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D VulkanRenderAPI::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
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

	SwapChainSupportDetails VulkanRenderAPI::QuerySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &details.Capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.Formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, details.Formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.PresentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, details.PresentModes.data());
		}

		return details;
	}

	QueueFamilyIndices VulkanRenderAPI::FindQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.GraphicsFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_Surface, &presentSupport);
			if (presentSupport) {
				indices.PresentFamily = i;
			}

			if (indices.IsComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}



	// Render Commands

	void VulkanRenderAPI::Clear()
	{
	}

	void VulkanRenderAPI::SetClearColor(vec4 color)
	{
	}

	void VulkanRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
	}

	void VulkanRenderAPI::SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height)
	{
	}
}
