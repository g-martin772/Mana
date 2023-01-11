#include "manapch.h"
#include "VulkanRenderAPI.h"

#include "Core/Application.h"

#include "VulkanPipeline.h"

namespace Mana {

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
		CreateInstance();
		InitDebugMessanger();
		m_SwapChain->InitSurface((GLFWwindow*)nativeWindow);
		m_PhysicalDevice->Init(m_SwapChain->GetSurface());
		m_Device->Init(m_PhysicalDevice, m_SwapChain->GetSurface());
		m_SwapChain->Init(m_Device);

		m_RenderPipeline->Init(m_SwapChain);
		m_FrameBuffer->Init(m_SwapChain, m_RenderPipeline);
	}

	void VulkanRenderAPI::Shutdown()
	{
		vkDeviceWaitIdle(m_Device->GetDevice());

		m_FrameBuffer->Clean();
		m_RenderPipeline->Clean();

		m_SwapChain->Clean();
		if (enableValidationLayers) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(s_Instance, "vkDestroyDebugUtilsMessengerEXT");
			func(s_Instance, m_DebugMessenger, nullptr);
		}
		m_Device->Clean();
		vkDestroyInstance(s_Instance, nullptr);
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
		if (vkCreateInstance(&createInfo, nullptr, &s_Instance) != VK_SUCCESS) {
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

		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(s_Instance, "vkCreateDebugUtilsMessengerEXT");
		MANA_CORE_ASSERT(func != nullptr, "Vulkan Debugmessanger Extension not present");

		VkResult result = func(s_Instance, &info, nullptr, &m_DebugMessenger);
		MANA_CORE_ASSERT(result == VK_SUCCESS, "Failed to set up debug messanger");
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



	// Render Commands

	void VulkanRenderAPI::Clear()
	{
	}

	void VulkanRenderAPI::SetClearColor(vec4 color)
	{
	}

	void VulkanRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		auto m_InFlightFence = m_FrameBuffer->GetInFlightFences()[m_FrameCount];
		vkWaitForFences(m_Device->GetDevice(), 1, &m_InFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(m_Device->GetDevice(), 1, &m_InFlightFence);

		uint32_t imageIndex;
		vkAcquireNextImageKHR(m_Device->GetDevice(), m_SwapChain->GetSwapchain(), UINT64_MAX, m_FrameBuffer->GetImageAvailableSemaphores()[m_FrameCount], VK_NULL_HANDLE, &imageIndex);

		vkResetCommandBuffer(m_FrameBuffer->GetCommandBuffers()[m_FrameCount], 0);
		m_FrameBuffer->RecordCommandBuffer(imageIndex, m_FrameCount, m_RenderPipeline);


		VkSemaphore waitSemaphores[] = { m_FrameBuffer->GetImageAvailableSemaphores()[m_FrameCount] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		auto commandBuffer = m_FrameBuffer->GetCommandBuffers()[m_FrameCount];

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		VkSemaphore signalSemaphores[] = { m_FrameBuffer->GetRenderFinishedSemaphores()[m_FrameCount]};
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_Device->GetGraphicsQueue(), 1, &submitInfo, m_InFlightFence) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { m_SwapChain->GetSwapchain() };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr;

		vkQueuePresentKHR(m_Device->GetPresentQueue(), &presentInfo); // Finally 2.0!!!

		m_FrameCount = (m_FrameCount + 1) % m_FrameBuffer->GetFramesOnFlight();
	}

	void VulkanRenderAPI::SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height)
	{
		// Recreate swapchain
	}
}
