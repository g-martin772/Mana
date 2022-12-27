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
        "vendor/spdlog/include",
        "vendor/glfw/include",
        "vendor/glad/include",
        "vendor/entt/single_include",
    }

    links {
        "glfw",
        "opengl32.lib",
        "glad"
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

    filter "configurations:Release"
        defines "MANA_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "MANA_DIST"
        runtime "Release"
        optimize "On"