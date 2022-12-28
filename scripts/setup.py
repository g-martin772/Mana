import os
import subprocess
import platform

from python import PythonConfiguration as PythonRequirements

PythonRequirements.Validate()

from premake import PremakeConfiguration as PremakeRequirements
from vulkan import VulkanConfiguration as VulkanRequirements

os.chdir('../')

premakeInstalled = PremakeRequirements.Validate()
VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--remote", "--merge"])

if (premakeInstalled):
    if platform.system() == "Windows":
        print("\nRunning premake...")
        subprocess.call([os.path.abspath("./scripts/GenProjFiles_Windows_vs2022.bat"), "nopause"])

    print("\nSetup completed!")
else:
    print("Mana requires Premake to generate project files.")