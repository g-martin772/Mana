#pragma once

#include "Core/Core.h"
#include "VulkanSwapChain.h"

#include "VulkanShader.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "VulkanVertexBuffer.h"

namespace Mana {
	class MANA_API VulkanPipeline {
	public:
		void Init();
		void Clean();

		inline VkPipeline GetPipeline() const { return m_GraphicsPipeline; }
		inline VkPipelineLayout GetPipelineLayout() const { return m_PipelineLayout; }
		inline VkRenderPass GetRenderPass() const { return m_RenderPass; }
	private:
		VkPipelineLayout m_PipelineLayout;
		VkPipeline m_GraphicsPipeline;

		VkRenderPass m_RenderPass;

		Ref<VulkanShader> m_Shader;
	};
}
