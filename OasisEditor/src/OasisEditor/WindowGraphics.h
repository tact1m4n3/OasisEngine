#pragma once

#include <string>

#include <glm/glm.hpp>

#include <Oasis/Oasis.h>

namespace OasisEditor {

	class WindowGraphics
	{
	public:
		static void DrawBoolControl(const std::string& label, bool& value);
		static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
		static void DrawColorControl(const std::string& label, glm::vec4& values, float columnWidth = 100.0f);
		static void DrawTextureControl(const std::string& label, std::string& lastTexturePath, float columnWidth = 100.0f);
	};

}

