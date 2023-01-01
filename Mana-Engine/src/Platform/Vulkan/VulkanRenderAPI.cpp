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

	void VulkanRenderAPI::Init()
	{
		CreateInstance();
	}

	void VulkanRenderAPI::Shutdown()
	{
		vkDestroyInstance(m_Instance, nullptr);
	}

	void VulkanRenderAPI::CreateInstance()
	{
		MANA_CORE_ASSERT(enableValidationLayers && !CheckValidationLayerSupport(), "validation layers requested, but not available!");
		

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Mana-App";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Mana-Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create vulkan instance");
		}

		MANA_CORE_INFO("Vulkan instance created with following extensions: ");
		for (int i = 0; i < glfwExtensionCount;)
			MANA_CORE_INFO("\t{0}: {1}", ++i, glfwExtensions[i]);
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
