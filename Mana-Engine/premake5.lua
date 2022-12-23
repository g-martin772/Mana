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
    }

    links{

    }

    -- filter "files:vendor/ImGuizmo/**.cpp"
    -- flags { "NoPCH" }

    -- filter "files:vendor/glm/glm/**.cpp"
    -- flags { "NoPCH" }

    -- filter "files:vendor/glm/glm/**.hpp"
    -- flags { "NoPCH" }

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