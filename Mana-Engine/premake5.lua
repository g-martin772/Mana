project "Mana-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    architecture "x64"

    configurations {
        "Debug",
        "Resease",
        "Dist"
    }

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/int/" .. outputdir .. "/%{prj.name}")

    pchheader "manapch.h"
    pchsource "src/manapch.cpp"

    files {
        "src/**.h",
        "src/**.cpp",
        "src/**.hpp",
        "src/**.inl",
        "src/**.c",
    }

    includedirs {
        "",
        "src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.shaderc}",
        "%{IncludeDir.SPIRV_Cross}",
        "%{IncludeDir.VulkanSDK}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.spdlog}",
    }

    links {
        "glfw",
        "opengl32.lib",
        "glad"
    }

    defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    filter "system:windows"
        systemversion "latest"

        defines {
            "MANA_PLATFORM_WINDOWS",
            "MANA_OPENGL",
        }

    filter "configurations:Debug"
        defines "MANA_DEBUG"
        runtime "Debug"
        symbols "On"

        links {
			"%{Library.ShaderC_Debug}",
			"%{Library.SPIRV_Cross_Debug}",
			"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

    filter "configurations:Release"
        defines "MANA_RELEASE"
        runtime "Release"
        optimize "On"

        links {
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

    filter "configurations:Dist"
        defines "MANA_DIST"
        runtime "Release"
        optimize "On"

        links {
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}