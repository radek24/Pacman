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
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    } 

    includedirs {
    }

    libdirs { 
    }

    links { 
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
