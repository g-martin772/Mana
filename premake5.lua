include "dependencies.lua"

workspace "Mana"
    startproject "Sandbox"
    architecture "x64"

    configurations {
        "Debug",
        "Resease",
        "Dist"
    }

group "Dependencies"
    include "Mana-Engine/vendor/glfw"
    include "Mana-Engine/vendor/glad"
    include "Mana-Engine/vendor/entt"
group ""

include "Mana-Engine"
include "Sandbox"
