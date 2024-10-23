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
    systemversion "latest"
    characterset "Unicode"
    architecture "x86_64"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.c"
    } 

    
    includedirs { 
        "Dependencies/SDL2/include", -- Include SDL headers
    }

    libdirs { 
        "Dependencies/SDL2/lib",
        "Dependencies/SDL2/bin"
    }

    links { 
        "SDL2","SDL2main" -- Link against SDL2
    }

    filter "configurations:Debug"
        defines {"PAC_DEBUG", "DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Development"
        defines {"PAC_DEVELOPMENT", "NDEBUG"}
        runtime "Release"
        optimize "Full"

    filter "configurations:Shipping"
        defines {"PAC_SHIPING", "NDEBUG"}
        runtime "Release"
        optimize "Full"


    filter "system:windows"
        postbuildcommands {

            "{COPY} ../Dependencies/SDL2/bin/SDL2.dll %{cfg.buildtarget.directory}"
        }