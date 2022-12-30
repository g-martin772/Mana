-- Output dir path
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Mana-Engine/vendor/stb_image"
IncludeDir["GLFW"] = "%{wks.location}/Mana-Engine/vendor/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/Mana-Engine/vendor/glad/include"
IncludeDir["entt"] = "%{wks.location}/Mana-Engine/vendor/entt/single_include"
IncludeDir["shaderc"] = "%{wks.location}/Mana-Engine/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Mana-Engine/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["spdlog"] = "%{wks.location}/Mana-Engine/vendor/spdlog/include"
IncludeDir["glm"] = "%{wks.location}/Mana-Engine/vendor/glm/include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
