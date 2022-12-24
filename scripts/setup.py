import os
import subprocess

os.chdir('../')

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--remote", "--merge"])

print("Running premake...")
subprocess.call(["vendor/premake/premake5.exe", "vs2022"])