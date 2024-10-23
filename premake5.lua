workspace "Pacman"
    platforms { "x64" }
    startproject "Pacman" 
   
    configurations {
        "Debug",
        "Development",
        "Shipping"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    filter { "system:windows", "action:gmake2" }
        buildoptions { "-Wall" }  -- Add any GCC specific build options here
        linkoptions { "-g" }      -- GCC linker options

project "Pacman"
    location "Pacman"
    kind "ConsoleApp"
    language "C"
    systemversion "latest"
    characterset "Unicode"
    architecture "x86_64"
    toolset "gcc"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c"
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
        buildoptions { "gcc -g" }

    filter "configurations:Development"
        defines {"PAC_DEVELOPMENT", "NDEBUG"}
        runtime "Release"
        optimize "Full"
        buildoptions { "gcc -g" }

    filter "configurations:Shipping"
        defines {"PAC_SHIPING", "NDEBUG"}
        runtime "Release"
        optimize "Full"
        buildoptions { "gcc" }