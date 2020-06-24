project "glad"
	language "C"
	kind "StaticLib"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/**.h",
        "include/KHR/**.h",
		"src/**.c"
    }
    
    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter {"system:windows" , "configurations:Release"}
        buildoptions "/MT"