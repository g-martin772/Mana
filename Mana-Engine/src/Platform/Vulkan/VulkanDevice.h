#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <optional>

namespace Mana {

	//Structs

	struct MANA_API QueueFamilys {
		std::optional<uint32_t> GraphicsFamily;
		std::optional<uint32_t> PresentFamily;

		bool IsComplete() {
			return GraphicsFamily.has_value() && PresentFamily.has_value();
		}
	};

	class MANA_API VulkanSwapChain;
	struct MANA_API SwapChainSupportDetails;

	// Physical

	class MANA_API VulkanPhysicalDevice {
	public:
		void Init(VkSurfaceKHR surface);

		VkPhysicalDevice GetDevice() const { return m_PhysicalDevice; }
		const QueueFamilys& GetQueueFamilys() const { return m_QueueFamilys; }
		const VkPhysicalDeviceProperties& GetProperties() const { return m_Properties; }
	private:
		bool IsSuitableDevice(VkPhysicalDevice device, VkSurfaceKHR surface);
		
	private:
		QueueFamilys m_QueueFamilys;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties m_Properties;
	};

	// Logical

	class MANA_API VulkanLogicalDevice {
	public:
		void Init(Ref<VulkanPhysicalDevice> physicalDevice, VkSurfaceKHR surface);
		void Clean();

		VkDevice GetDevice() const { return m_Device; }
		const Ref<VulkanPhysicalDevice>& GetPhysicalDevice() const { return m_PhysicalDevice; }
		VkQueue GetGraphicsQueue() const { return m_GraphicsQueue; }
		VkQueue GetPresentQueue() const { return m_PresentQueue; }
	private:
		Ref<VulkanPhysicalDevice> m_PhysicalDevice;

		VkDevice m_Device;
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;
	};
}

#include "Platform/Vulkan/VulkanSwapChain.h"
