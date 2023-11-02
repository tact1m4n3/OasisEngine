workspace "Oasis"
    architecture "x64"
    startproject "OasisEditor"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Oasis/vendor/GLFW/include"
IncludeDir["Glad"] = "Oasis/vendor/glad/include"
IncludeDir["ImGui"] = "Oasis/vendor/imgui"
IncludeDir["glm"] = "Oasis/vendor/glm"
IncludeDir["stb_image"] = "Oasis/vendor/stb_image"
IncludeDir["entt"] = "Oasis/vendor/entt"

group "Dependencies"
	include "Oasis/vendor/glfw"
	include "Oasis/vendor/glad"
	include "Oasis/vendor/imgui"
group ""

project "Oasis"
	location "Oasis"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}
	sysincludedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"OASIS_WINDOWS"
		}

	filter "system:macosx"
		defines
		{
			"OASIS_MACOSX"
		}

	filter "system:linux"
		defines
		{
			"OASIS_LINUX"
		}

	filter "configurations:Debug"
		defines "OASIS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OASIS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OASIS_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Oasis/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	sysincludedirs
	{
		"%{prj.name}/src",
		"Oasis/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Oasis",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"OASIS_WINDOWS"
		}

	filter "system:macosx"
		defines
		{
			"OASIS_MACOSX"
		}

	filter "system:linux"
		defines
		{
			"OASIS_LINUX"
		}

	filter "configurations:Debug"
		defines "OASIS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OASIS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OASIS_DIST"
		runtime "Release"
		optimize "on"

project "OasisEditor"
	location "OasisEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"Oasis/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	sysincludedirs
	{
		"%{prj.name}/src",
		"Oasis/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Oasis",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"OASIS_WINDOWS"
		}

	filter "system:macosx"
		defines
		{
			"OASIS_MACOSX"
		}

	filter "system:linux"
		defines
		{
			"OASIS_LINUX"
		}

	filter "configurations:Debug"
		defines "OASIS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OASIS_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OASIS_DIST"
		runtime "Release"
		optimize "on"