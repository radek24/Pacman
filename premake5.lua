workspace "Pacman"
    platforms { "x64" }
    startproject "Pacman" 
   
    configurations {
        "Debug",
        "Development",
        "Shipping"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pacman"
    location "Pacman"
    kind "ConsoleApp"
    language "C"
    architecture "x86_64"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.c"
    } 

    
    includedirs { 
        "Dependencies/SDL2/include",
        "Dependencies/SDL2_Image/include",
        "Dependencies/SDL2_ttf/include"
    }

    libdirs { 
        "Dependencies/SDL2/lib",
        "Dependencies/SDL2_Image/lib/x64",
        "Dependencies/SDL2_ttf/lib/x64",
    }

    links { 
        "SDL2","SDL2main","SDL2_image","SDL2_ttf"
    }



    filter "configurations:Debug"
        defines {"PAC_DEBUG", "DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Development"
        defines {"PAC_DEVELOPMENT", "NDEBUG"}
        runtime "Release"
        optimize "On"
 

    filter "configurations:Shipping"
        defines {"PAC_SHIPING", "NDEBUG"}
        runtime "Release"
        optimize "On"
        

    filter "system:windows"
        postbuildcommands {
            "{COPY} ../Dependencies/SDL2/bin/SDL2.dll %{cfg.buildtarget.directory}",
            "{COPY} ../Dependencies/SDL2_image/lib/x64/SDL2_image.dll %{cfg.buildtarget.directory}",
            "{COPY} ../Dependencies/SDL2_ttf/lib/x64/SDL2_ttf.dll %{cfg.buildtarget.directory}"
        }