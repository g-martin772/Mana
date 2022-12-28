#pragma once

#include "Core/Core.h"
#include "Math/Math.h"

#include <string>
#include <unordered_map>

namespace Mana {
	class MANA_API Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArr(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string FragmentSrc);
	private:
	};

	class MANA_API ShaderLibrary {
	public:
		void Add(const Ref<Shader>& s);
		void Add(const std::string& name, const Ref<Shader>& s);

		Ref<Shader> Load(const std::string& path);
		Ref<Shader> Load(const std::string& name, const std::string& path);
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}