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
        "%{prj.name}/Source/**.c",
        "%{prj.name}/Vendor/log/**.h",
        "%{prj.name}/Vendor/log/**.c",
        "%{prj.name}/Vendor/ini/**.h",
        "%{prj.name}/Vendor/ini/**.c"
    } 
    
    includedirs { 
        "%{prj.name}/Vendor",
        "Dependencies/SDL2/include",
        "Dependencies/SDL2_Image/include",
        "Dependencies/SDL2_ttf/include",
        "%{prj.location}/Source"
    }

    links { 
        "SDL2main","SDL2","SDL2_image","SDL2_ttf"
    }

    postbuildcommands{
        "{COPY} ../Pacman/Resources %{cfg.buildtarget.directory}/Resources"
    }

    --OS Specific stuff

    filter "system:macosx"
        defines {"PLATFORM_MAC"}
        links { "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "CoreAudio.framework", "AudioToolbox.framework" }
        
        libdirs { 
            "/opt/homebrew/lib"
        }

    filter "system:windows"
        defines {"PLATFORM_WINDOWS"}
        postbuildcommands {
            "{COPY} ../Dependencies/SDL2/lib/x64/SDL2.dll %{cfg.buildtarget.directory}",
            "{COPY} ../Dependencies/SDL2_image/lib/x64/SDL2_image.dll %{cfg.buildtarget.directory}",
            "{COPY} ../Dependencies/SDL2_ttf/lib/x64/SDL2_ttf.dll %{cfg.buildtarget.directory}"
        }
        libdirs { 
            "Dependencies/SDL2/lib/x64",
            "Dependencies/SDL2_Image/lib/x64",
            "Dependencies/SDL2_ttf/lib/x64",
        }
    
    filter { "system:windows", "action:gmake2" }
        toolset "gcc"
        makesettings [[ CC = gcc ]]

    filter "system:linux"
        defines {"PLATFORM_LINUX"}
        buildoptions {
            "-Wall",
            "-Wextra",
            "-pedantic",
            "-Werror=uninitialized",
            "-Werror=return-type",
            "-Wconversion",
            "-Wno-unused-variable",
            "-Wno-unused-parameter"
        }

    --Configuration Specific stuff
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