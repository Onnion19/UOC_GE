
workspace "GameEngine"
    configurations { "Debug", "Release"}
    platforms {"Win32", "x64"}
	cdialect "C99"
    cppdialect "C++latest"
	
	startproject "Engine" 

	defines{ "_XM_NO_INTRINSICS_", "WIN32", "_WINDOWS"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
		
  
		

    filter {}

	project "Engine"
		kind "ConsoleApp"
		
		location "build/%{prj.name}"
		targetdir "Executable/%{cfg.buildcfg}/"
		objdir ("bin/int/" .. "%{cfg.buildcfg}")
		
		language "C++"
		includedirs{"Source/include", "Source/src", "Source", "ThirdParty/expat", "ThirdParty/autodesk/include"}		
		
		files {"Source/**.h","Source/*.hpp", "Source/**.cpp", "ThirdParty/**.h", "ThirdParty/**.cpp"}
		links {
		"d3d11",
        "libfbxsdk-md",
        "libxml2-md",
        "zlib-md",
        "winmm",
        "libexpat64",
        "D3DCompiler",
        "dinput8",
        "dxguid"}
		libdirs { "ThirdParty/expat"}

		
		filter "configurations:Release"
			defines { "NDEBUG" }
			optimize "On"
			libdirs { "ThirdParty/autodesk/release" }
			
		filter "configurations:Debug"
			defines { "DEBUG" }
			symbols "On"
			libdirs { "ThirdParty/autodesk/debug" }
			
		filter { "platforms:x64" }
			architecture "x86_64"
			
		
		
	

