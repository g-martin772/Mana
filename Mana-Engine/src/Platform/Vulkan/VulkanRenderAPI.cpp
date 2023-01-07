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

	void VulkanRenderAPI::Init()
	{
		CreateInstance();
		InitDebugMessanger();
		PickPhysicalDevice();
		CreateLogicalDevice();
	}

	void VulkanRenderAPI::Shutdown()
	{
		vkDestroyDevice(m_Device, nullptr);

		if (enableValidationLayers) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
			func(m_Instance, m_DebugMessenger, nullptr);
		}

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

		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily.value();
		queueCreateInfo.queueCount = 1;
		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;

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
	}

	bool VulkanRenderAPI::IsSuitableDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		QueueFamilyIndices indices = FindQueueFamilies(device);

		return indices.IsComplete() &&
			   deviceFeatures.geometryShader;
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
