#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"

#include "VulkanDevice.h"

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Mana {
	using ShaderMap = std::unordered_map<VkShaderStageFlagBits, std::vector<uint32_t>>;
	using ShaderSourceMap = std::unordered_map<VkShaderStageFlagBits, std::string>;
	using ShaderModuleMap = std::unordered_map<VkShaderStageFlagBits, VkShaderModule>;

	class MANA_API VulkanShader : public Shader {
	public:
		VulkanShader(const std::string& path);
		virtual ~VulkanShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArr(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const vec2& value) override;
		virtual void SetFloat3(const std::string& name, const vec3& value) override;
		virtual void SetFloat4(const std::string& name, const vec4& value) override;
		virtual void SetMat4(const std::string& name, const mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		//Uniforms
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const vec2& value);
		void UploadUniformFloat3(const std::string& name, const vec3& value);
		void UploadUniformFloat4(const std::string& name, const vec4& value);

		void UploadUniformMat4(const std::string& name, const mat4& matrix);

		inline ShaderModuleMap GetShaders() const { return m_Shaders; }
		inline VkShaderModule GetShader(VkShaderStageFlagBits stage) const { return m_Shaders.at(stage); }
	private:
		std::string ReadFile(const std::string& filepath);
		ShaderSourceMap PreProcess(const std::string& source);

		// Compilation
		void CompileVulkanBinarys();
		void CreateShaderModules();
	private:
		std::string m_Name, m_Path;

		ShaderMap m_VulkanSPIRV;

		ShaderModuleMap m_Shaders;
	};
}
