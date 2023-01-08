#include "manapch.h"
#include "VulkanShader.h"

#include <shaderc/shaderc.hpp>

namespace Mana {
	std::vector<char> ReadFile(std::string path) {
		std::ifstream in(path, std::ios::binary);
		std::vector<char> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		return bytes;
	}

	VulkanShader::VulkanShader(std::string pathIn, std::string pathOut) 
		: m_SourcePath(pathIn), m_BinPath(pathOut)
	{
	}

	VulkanShader::~VulkanShader()
	{
	}

	void VulkanShader::Compile(const Ref<VulkanLogicalDevice>& device, bool vertexShader)
	{
		// Read in file
		std::ifstream in(m_SourcePath);
		std::string source((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

		// Create a compiler instance
		shaderc::Compiler compiler;

		// Set the compiler options
		shaderc::CompileOptions options;
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);

		// Compile the GLSL source code to SPIR-V
		shaderc::SpvCompilationResult result;

		if(vertexShader)
			result = compiler.CompileGlslToSpv(source, shaderc_glsl_vertex_shader, "shader.vert", options);
		else
			result = compiler.CompileGlslToSpv(source, shaderc_glsl_fragment_shader, "shader.frag", options);


		MANA_CORE_ASSERT(result.GetCompilationStatus() == shaderc_compilation_status_success, "Failed to compile shader");

		std::vector<uint32_t> spirv(result.cbegin(), result.cend());

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = spirv.size() * 4;
		createInfo.pCode = spirv.data();
		if (vkCreateShaderModule(device->GetDevice(), &createInfo, nullptr, &m_Shader) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create shader module!");
		}
	}
}
