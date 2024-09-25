
workspace "GameEngine"
    configurations { "Debug", "Release"}
    platforms { "x64", "x86"}
	defaultplatform ("x64")
	cdialect "C99"
    cppdialect "C++latest"
	
	startproject "Engine" 

	defines{ "_XM_NO_INTRINSICS_"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "platforms:x64" }
        architecture "x86_64"
		

    filter {}

	project "Engine"
		kind "ConsoleApp"
		
		location "build/%{prj.name}"
		targetdir "Executable/%{cfg.buildcfg}/"
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		language "C++"
		includedirs{"Source/include", "Source/src", "Source", "ThirdParty/expat", "ThirdParty/autodesk/include"}		
		
		files {"Source/**.h","Source/*.hpp", "Source/**.cpp", "ThirdParty/**.h", "ThirdParty/**.cpp"}
		links {"libexpat64", "libfbxsdk" }
		libdirs { "ThirdParty/expat", "ThirdParty/autodesk" }
		
		
	

