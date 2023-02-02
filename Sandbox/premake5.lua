project "Sandbox"
        kind "ConsoleApp"
        staticruntime "off"

        language "C++"
        cppdialect "C++17"

        architecture "x64"

        configurations {
            "Debug",
            "Resease",
            "Dist"
        }

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/int/" .. outputdir .. "/%{prj.name}")

        files {
           "src/**.h",
           "src/**.hpp",
           "src/**.cpp",
           "src/**.c"
        }

        includedirs {
            "%{wks.location}/Mana-Engine/src",
            "%{IncludeDir.entt}",
            "%{IncludeDir.spdlog}",
            "%{IncludeDir.glm}",
        }

        links{
            "Mana-Engine",
        }
    
        filter "system:windows"
            systemversion "latest"
            defines "MANA_PLATFORM_WINDOWS"
    
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