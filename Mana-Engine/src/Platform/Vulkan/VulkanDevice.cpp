#include "manapch.h"
#include "VulkanDevice.h"

#include "Platform/Vulkan/VulkanRenderAPI.h"
#include "Platform/Vulkan/VulkanSwapChain.h"

namespace Mana {

	// Utils

	QueueFamilys FindQueueFamilies(VkSurfaceKHR surface, VkPhysicalDevice device)
	{
		QueueFamilys indices;

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
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
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

	// Physical Device

	void VulkanPhysicalDevice::Init(VkSurfaceKHR surface)
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(VulkanRenderAPI::GetInstance(), &deviceCount, nullptr);

		MANA_CORE_ASSERT(deviceCount != 0, "No GPU with Vulkan support found!");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(VulkanRenderAPI::GetInstance(), &deviceCount, devices.data());

		for (const auto& device : devices) {
			if (IsSuitableDevice(device, surface)) {
				m_PhysicalDevice = device;
				break;
			}
		}

		MANA_CORE_ASSERT(m_PhysicalDevice != VK_NULL_HANDLE, "No suitable GPU found!");
	}

	bool VulkanPhysicalDevice::IsSuitableDevice(VkPhysicalDevice  device, VkSurfaceKHR surface)
	{
		// Get device info
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// GetQueueFamilies
		QueueFamilys indices = FindQueueFamilies(surface, device);


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
			SwapChainSupportDetails swapChainSupport = VulkanSwapChain::QuerySwapChainSupport(device, surface);
			swapChainAdequate = !swapChainSupport.Formats.empty() && !swapChainSupport.PresentModes.empty();
		}

		return indices.IsComplete() &&
			deviceFeatures.geometryShader &&
			requiredExtensions.empty() &&
			swapChainAdequate;
	}

	// Logical Device

	void VulkanLogicalDevice::Init(Ref<VulkanPhysicalDevice> physicalDevice, VkSurfaceKHR surface)
	{
		m_PhysicalDevice = physicalDevice;

		QueueFamilys indices = FindQueueFamilies(surface, m_PhysicalDevice->GetDevice());

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

		VkResult result = vkCreateDevice(m_PhysicalDevice->GetDevice(), &createInfo, nullptr, &m_Device);
		MANA_CORE_ASSERT(result == VK_SUCCESS, "Failed to create logical Device!");

		vkGetDeviceQueue(m_Device, indices.GraphicsFamily.value(), 0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_Device, indices.PresentFamily.value(), 0, &m_PresentQueue);
	}

	void VulkanLogicalDevice::Clean()
	{
		vkDestroyDevice(m_Device, nullptr);
	}
}
