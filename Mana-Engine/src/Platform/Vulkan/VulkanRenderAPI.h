#pragma once

#include "Core/Core.h"
#include "Renderer/RenderAPI.h"
#include "Platform/Vulkan/VulkanDevice.h"
#include "VulkanFrameBuffer.h"
#include "VulkanPipeline.h"
#include "VulkanShader.h"

#include <optional>
#include <set>
#include <limits>
#include <algorithm>

namespace Mana {
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	class MANA_API VulkanRenderAPI : public RenderAPI {
	public:
		virtual void Init(void* nativeWindow) override;
		virtual void Shutdown() override;
		virtual void Clear() override;
		virtual void SetClearColor(vec4 color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		virtual void SetViewport(uint32_t originX, uint32_t originY, uint32_t width, uint32_t height) override;

		inline static VulkanRenderAPI* Get() { return static_cast<VulkanRenderAPI*>(RenderAPI::GetRenderAPI()); }
		inline static VkInstance GetInstance() { return s_Instance; }
		inline static Ref<VulkanLogicalDevice> GetDevice() { return Get()->m_Device; }
		inline static Ref<VulkanPhysicalDevice> GetPhysicalDevice() { return Get()->m_PhysicalDevice; }
		inline static Ref<VulkanSwapChain> GetCurrentSwapchain() { return Get()->m_SwapChain; }
		inline static Ref<VulkanPipeline> GetCurrentPipeline() { return Get()->m_RenderPipeline; }
		inline static Ref<VulkanFrameBuffer> GetCurrentFrameBuffer() { return Get()->m_FrameBuffer; }
		inline static std::vector<Ref<VulkanVertexBuffer>> GetVertexBuffers() { return Get()->m_VertexBuffers; }
	private:
		void CreateInstance();
		void InitDebugMessanger();


		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();


	private:
		inline static VkInstance s_Instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

		std::vector<Ref<VulkanVertexBuffer>> m_VertexBuffers;

		Ref<VulkanPhysicalDevice> m_PhysicalDevice = std::make_shared<VulkanPhysicalDevice>();
		Ref<VulkanLogicalDevice> m_Device = std::make_shared<VulkanLogicalDevice>();
		Ref<VulkanSwapChain> m_SwapChain = std::make_shared<VulkanSwapChain>();
		Ref<VulkanPipeline> m_RenderPipeline = std::make_shared<VulkanPipeline>();
		Ref<VulkanFrameBuffer> m_FrameBuffer = std::make_shared<VulkanFrameBuffer>();

		uint32_t m_FrameCount = 0;
	};
}
