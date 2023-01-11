#include "manapch.h"
#include "VulkanShader.h"

#include "VulkanRenderAPI.h"

#include <shaderc/shaderc.hpp>

namespace Mana {

	// Utils

	inline constexpr static const char* GetCacheDirectory() {
		return "assets/cache/shader/vulkan";
	}

	inline static void CreateCacheDirectoryIfNeeded() {
		if (!std::filesystem::exists(GetCacheDirectory()))
			std::filesystem::create_directories(GetCacheDirectory());
	}

	inline constexpr static const char* VkShaderStageCachedFileExtension(VkShaderStageFlagBits stage) {
		switch (stage)
		{
		case VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT:    return ".cached.vert";
		case VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT:  return ".cached.frag";
		}

		MANA_CORE_ASSERT(false, "Unknown shader type!");
		return ".cached.shader";
	}

	inline static VkShaderStageFlagBits ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return VK_SHADER_STAGE_VERTEX_BIT;
		if (type == "fragment" || type == "pixel")
			return VK_SHADER_STAGE_FRAGMENT_BIT;

		MANA_CORE_ASSERT(false, "Unknown shader type!");
		return (VkShaderStageFlagBits)0;
	}

	std::string VulkanShader::ReadFile(const std::string& path) {
		std::ifstream in(path, std::ios::binary);
		std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		return src;
	}

	ShaderSourceMap VulkanShader::PreProcess(const std::string& source)
	{
		ShaderSourceMap shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			MANA_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			MANA_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			MANA_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	// Shader impl

	VulkanShader::VulkanShader(const std::string& path)
		: m_Path(path)
	{
		CreateCacheDirectoryIfNeeded();

		// Get shader name from file name
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count);

		std::filesystem::path cPath = m_Path;
		std::filesystem::path cacheDir = GetCacheDirectory();
		auto binVerPath = cacheDir / (cPath.filename().string() + VkShaderStageCachedFileExtension(VK_SHADER_STAGE_VERTEX_BIT));
		auto binFragPath = cacheDir / (cPath.filename().string() + VkShaderStageCachedFileExtension(VK_SHADER_STAGE_FRAGMENT_BIT));
		std::ifstream inVert(binVerPath, std::ios::in | std::ios::binary);
		std::ifstream inFrag(binFragPath, std::ios::in | std::ios::binary);

		if (!inVert.is_open() || !inFrag.is_open()) 
		{
			MANA_CORE_INFO("Compiling Shader: {0}", m_Name);
			auto start = std::chrono::high_resolution_clock::now();
			CompileVulkanBinarys();
			auto duration = std::chrono::high_resolution_clock::now() - start;
			MANA_CORE_WARN("Shader creation took {0} ms", duration.count() / 1000000);
		} 
		else
		{
			std::string vertSource((std::istreambuf_iterator<char>(inVert)), std::istreambuf_iterator<char>());
			m_VulkanSPIRV[VK_SHADER_STAGE_VERTEX_BIT] = std::vector<uint32_t>(vertSource.begin(), vertSource.end());
			std::string fragSource((std::istreambuf_iterator<char>(inFrag)), std::istreambuf_iterator<char>());
			m_VulkanSPIRV[VK_SHADER_STAGE_FRAGMENT_BIT] = std::vector<uint32_t>(fragSource.begin(), fragSource.end());
		}

		CreateShaderModules();
	}

	VulkanShader::~VulkanShader()
	{
	}

	void VulkanShader::Bind() const
	{
	}

	void VulkanShader::UnBind() const
	{
	}

	void VulkanShader::SetInt(const std::string& name, int value)
	{
	}

	void VulkanShader::SetIntArr(const std::string& name, int* values, uint32_t count)
	{
	}

	void VulkanShader::SetFloat(const std::string& name, float value)
	{
	}

	void VulkanShader::SetFloat2(const std::string& name, const vec2& value)
	{
	}

	void VulkanShader::SetFloat3(const std::string& name, const vec3& value)
	{
	}

	void VulkanShader::SetFloat4(const std::string& name, const vec4& value)
	{
	}

	void VulkanShader::SetMat4(const std::string& name, const mat4& value)
	{
	}

	void VulkanShader::UploadUniformInt(const std::string& name, int value)
	{
	}

	void VulkanShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
	}

	void VulkanShader::UploadUniformFloat(const std::string& name, float value)
	{
	}

	void VulkanShader::UploadUniformFloat2(const std::string& name, const vec2& value)
	{
	}

	void VulkanShader::UploadUniformFloat3(const std::string& name, const vec3& value)
	{
	}

	void VulkanShader::UploadUniformFloat4(const std::string& name, const vec4& value)
	{
	}

	void VulkanShader::UploadUniformMat4(const std::string& name, const mat4& matrix)
	{
	}

	void VulkanShader::CompileVulkanBinarys()
	{
		// Read in file
		auto src = PreProcess(ReadFile(m_Path));
		

		// Create a compiler instance
		shaderc::Compiler compiler;

		// Set the compiler options
		shaderc::CompileOptions options;
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);

		// Compile the GLSL source code to SPIR-V
		shaderc::SpvCompilationResult vertResult;
		shaderc::SpvCompilationResult fragResult;

		vertResult = compiler.CompileGlslToSpv(src[VK_SHADER_STAGE_VERTEX_BIT], shaderc_glsl_vertex_shader, "shader.vert", options);
		fragResult = compiler.CompileGlslToSpv(src[VK_SHADER_STAGE_FRAGMENT_BIT], shaderc_glsl_fragment_shader, "shader.frag", options);


		MANA_CORE_ASSERT(vertResult.GetCompilationStatus() == shaderc_compilation_status_success, "Failed to compile vertex shader");
		MANA_CORE_ASSERT(fragResult.GetCompilationStatus() == shaderc_compilation_status_success, "Failed to compile fragment shader");


		std::vector<uint32_t> vertSpirv(vertResult.cbegin(), vertResult.cend());
		std::vector<uint32_t> fragSpirv(fragResult.cbegin(), fragResult.cend());

		m_VulkanSPIRV[VK_SHADER_STAGE_VERTEX_BIT] = vertSpirv;
		m_VulkanSPIRV[VK_SHADER_STAGE_FRAGMENT_BIT] = fragSpirv;
	}
	
	void VulkanShader::CreateShaderModules()
	{
		auto device = VulkanRenderAPI::GetDevice();

		VkShaderModuleCreateInfo vertCreateInfo{};
		vertCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		vertCreateInfo.codeSize = m_VulkanSPIRV[VK_SHADER_STAGE_VERTEX_BIT].size() * 4;
		vertCreateInfo.pCode = m_VulkanSPIRV[VK_SHADER_STAGE_VERTEX_BIT].data();
		if (vkCreateShaderModule(device->GetDevice(), &vertCreateInfo, nullptr, &m_Shaders[VK_SHADER_STAGE_VERTEX_BIT]) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create vertex shader module!");
		}

		VkShaderModuleCreateInfo fragCreateInfo{};
		fragCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		fragCreateInfo.codeSize = m_VulkanSPIRV[VK_SHADER_STAGE_FRAGMENT_BIT].size() * 4;
		fragCreateInfo.pCode = m_VulkanSPIRV[VK_SHADER_STAGE_FRAGMENT_BIT].data();
		if (vkCreateShaderModule(device->GetDevice(), &fragCreateInfo, nullptr, &m_Shaders[VK_SHADER_STAGE_FRAGMENT_BIT]) != VK_SUCCESS) {
			MANA_CORE_ASSERT(false, "Failed to create fragment shader module!");
		}
	}
}
