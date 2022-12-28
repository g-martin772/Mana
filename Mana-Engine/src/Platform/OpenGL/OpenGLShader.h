#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Mana {
	class MANA_API OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

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
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		// Compilation
		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
	private:
		uint32_t m_RendererID;
		std::string m_Path;
		std::string m_Name;

		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;

		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	};
}