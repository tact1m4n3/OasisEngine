#include <OasisEditor/WindowGraphics.h>

#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_internal.h>

using namespace Oasis;

namespace OasisEditor {

	void WindowGraphics::DrawBoolControl(const std::string& label, bool& value)
	{
		ImGui::Checkbox(label.c_str(), &value);
	}

	void WindowGraphics::DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void WindowGraphics::DrawColorControl(const std::string& label, glm::vec4& values, float columnWidth)
	{
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();
		
		if (ImGui::ColorButton(label.c_str(), *(ImVec4*)glm::value_ptr(values), 0, { ImGui::CalcItemWidth() + 50.0f, lineHeight }))
			ImGui::OpenPopup("MyColorPicker");

		if (ImGui::BeginPopup("MyColorPicker"))
		{
			ImGui::ColorPicker4("##ColorPicker", glm::value_ptr(values));
			ImGui::EndPopup();
		}

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void WindowGraphics::DrawTextureControl(const std::string& label, std::string& texturePath, float columnWidth)
	{
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		{
			Texture* tex = (Texture*)ResourceManager::Get(texturePath);
			if (tex)
			{
				if (ImGui::ImageButton((ImTextureID)tex->GetRendererId(), { ImGui::CalcItemWidth() + 50.0f, lineHeight }, { 0, 0 }, { 1, 1 }, 0))
				{
					texturePath = FileDialogs::OpenFile("*.png");
				}
			}
			else
			{
				if (ImGui::ImageButton(0, { ImGui::CalcItemWidth() + 50.0f, lineHeight }, { 0, 0 }, { 1, 1 }, 0))
				{
					texturePath = FileDialogs::OpenFile("*.png");
				}
			}
		}

		ImGui::Columns(1);

		ImGui::PopID();
	}

}
