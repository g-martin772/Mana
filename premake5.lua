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
group ""

include "Mana-Engine"
include "Sandbox"
