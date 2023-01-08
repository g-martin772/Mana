#pragma once

#include "Core/Core.h"
#include "VulkanDevice.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	class MANA_API VulkanShader { 
	// TODO: Implement high level shader interface
	public:
		VulkanShader(std::string pathIn, std::string pathOut);
		~VulkanShader();

		void Compile(const Ref<VulkanLogicalDevice>& device, bool vertexShader);
		VkShaderModule GetShader() const { return m_Shader; }
	private:
		std::string m_SourcePath, m_BinPath;
		VkShaderModule m_Shader;
	};
}
