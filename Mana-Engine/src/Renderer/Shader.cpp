#include "manapch.h"
#include "Shader.h"

#include "Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Mana {
    Ref<Shader> Mana::Shader::Create(const std::string& path)
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None:
            MANA_CORE_ERROR("No Render API Selected");
            return nullptr;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(path);
        }

        MANA_CORE_ERROR("Invalid Render API");
        __debugbreak();
        return nullptr;
    }
    
    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string fragmentSrc)
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None:
            MANA_CORE_ERROR("No Render API Selected");
            return nullptr;
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        MANA_CORE_ERROR("Invalid Render API");
        __debugbreak();
        return nullptr;
    }
   
    // Shader library
    
    
    void ShaderLibrary::Add(const Ref<Shader>& s)
    {
        const std::string& name = s->GetName();
        Add(name, s);
    }
    
    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& s)
    {
        if (!Exists(name))
            m_Shaders[name] = s;
    }
    
    Ref<Shader> ShaderLibrary::Load(const std::string& path)
    {
        Ref<Shader> shader = Shader::Create(path);
        Add(shader);
        return shader;
    }
    
    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
    {
        Ref<Shader> shader = Shader::Create(path);
        Add(name, shader);
        return shader;
    }
    
    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        if (Exists(name))
            return m_Shaders[name];
        else
            MANA_CORE_ERROR("Shader \"{0}\" not found!", name);
        __debugbreak();
        return nullptr;
    }
    
    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
