-- Algorithms
workspace "Algorithms"
    startproject "Algorithms"
    architecture "x64"
    configurations { "Debug"--[[, "Release"--]] }

    warnings "Extra"
    flags { "FatalWarnings" }

    filter "configurations:Debug"
        defines { "HTN_DEBUG" }
        symbols "On"

    --[[filter "configurations:Release"
        defines { "HTN_RELEASE" }
        optimize "On"--]]

    filter "system:windows"
        systemversion "latest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Algorithms
project "Algorithms"
    location "Algorithms"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/src/pch.cpp"
    forceincludes "pch.h"

    files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.h" }

    includedirs { "%{prj.name}/src" }

    nuget { "Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1.7" }
