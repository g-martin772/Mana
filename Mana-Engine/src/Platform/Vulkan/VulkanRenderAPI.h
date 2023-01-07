#pragma once

#include "Core/Core.h"
#include "Renderer/RenderAPI.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <optional>

namespace Mana {
	struct QueueFamilyIndices {
		std::optional<uint32_t> GraphicsFamily;

		bool IsComplete() {
			return GraphicsFamily.has_value();
		}
	};

	class MANA_API VulkanRenderAPI : public RenderAPI {
	public:
		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void Clear() override;
		virtual void SetClearColor(vec4 color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) override;
	private:
		void CreateInstance();
		void InitDebugMessanger();
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		bool IsSuitableDevice(VkPhysicalDevice device);
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	private:
		VkInstance m_Instance;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device;
		VkQueue m_GraphicsQueue;
		VkDebugUtilsMessengerEXT m_DebugMessenger;
	};
}
