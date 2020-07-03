workspace "FluidDynamics"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["googletest"] = "googletest/googletest/include"
IncludeDir["glad"] = "vendors/glad/include"
IncludeDir["glslang"] = "SPIRV-Cross/external/glslang-build/output/include/glslang/Include"
IncludeDir["spirv_tool"] = "SPIRV-Cross/external/spirv-tools-build/output/include"
IncludeDir["spirv_cross"] = "SPIRV-Cross/include"
IncludeDir["glfw"] = "vendors/glfw-3.3.2/include"
IncludeDir["spdlog"] = "vendors/spdlog/include"

LibDir = {}
LibDir["googletest"] = "googletest/googletest/build/lib/Debug"
LibDir["glfw"] = "vendors/glfw-3.3.2/lib-vc2019"
LibDir["glslang"] = "SPIRV-Cross/external/glslang-build/output/lib"
LibDir["spirv_tool"] = "SPIRV-Cross/external/spirv-tools-build/output/lib"
LibDir["spirv_cross"] = "SPIRV-Cross/build/Debug"
include "vendors/glad"



-- googltest uses /MT by defualt in the VS project setting == >Causes the application to use the multithread, static version of the run-time library. Defines _MT and causes the compiler to place the library name LIBCMT.lib into the .obj file so that the linker will use LIBCMT.lib to resolve external symbols.
-- to change that we need to add line in CMAKE file of the googletest solution ==> set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE) by doing this we make it to use /MD
-- the upper line will not effect because in the inne cmake file there is a line which makes gtest_force_shared_crt OFF ---> it is on the first line of the cmake file by making it ON we can build our solution.
-- also we need to define the google test version in the cmake file.
-- also it needs project to be in Debug mode so we must add runtime "Debug"
project "sample"
	location "sample"
	language "C++"
	kind "ConsoleApp"
	runtime "Debug"


	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/imgui/**.h",
		"%{prj.name}/src/imgui/**.cpp",
		"%{prj.name}/src/Event/**.h",
		"%{prj.name}/src/Event/**.cpp",
		"%{prj.name}/shader/**.hlsl",
		"%{prj.name}/shader/**.vert",
		"%{prj.name}/shader/**.frag",
		"%{prj.name}/shader/**.spv",
	}

	includedirs
	{
		"%{IncludeDir.googletest}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glslang}",
		"%{IncludeDir.spirv_tool}",
		"%{IncludeDir.spirv_cross}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.spdlog}",
	}
	libdirs
	{
		"%{LibDir.googletest}",
		"%{LibDir.glfw}",
		"%{LibDir.glslang}",
		"%{LibDir.spirv_tool}",
		"%{LibDir.spirv_cross}"
	}
	links
	{
		"gtest_maind",
		"gtestd",
		"glad",
		"glfw3",
		"opengl32",
		"glslang",
		"HLSL",
		"OGLCompiler",
		"OSDependent",
		"SPIRV",
		"SPVRemapper",
		"SPIRV-Tools",
		"SPIRV-Tools-link",
		"SPIRV-Tools-opt",
		"SPIRV-Tools-reduce",
		"SPIRV-Tools-shared",
		"spirv-cross-cd",
		"spirv-cross-cored",
		"spirv-cross-cppd",
		"spirv-cross-glsld",
		"spirv-cross-hlsld",
		"spirv-cross-msld",
		"spirv-cross-reflectd",
		"spirv-cross-utild"
	}
