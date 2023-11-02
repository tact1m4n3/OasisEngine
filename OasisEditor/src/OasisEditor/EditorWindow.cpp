#include <OasisEditor/EditorWindow.h>

#include <iostream>

#include <imgui.h>

namespace OasisEditor {

	EditorWindow::EditorWindow(const std::string& title, int flags)
		: m_Title(title), m_Flags(flags)
	{
	}
	
	void EditorWindow::Begin()
	{
		ImGui::SetNextWindowSize({ 600, 400 }); // default size

		StylePush();
		ImGui::Begin(m_Title.c_str(), &m_Show, m_Flags);
		StylePop();
	}

	void EditorWindow::End()
	{
		ImGui::End();
	}

	void EditorWindow::OnImGuiRender()
	{
		if (!m_Show)
			return;

		Begin();
		OnContentDraw();
		End();
	}

}
