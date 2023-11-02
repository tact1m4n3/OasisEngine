#include "EditorExtension.h"

#include <iostream>

#include <imgui.h>

using namespace Oasis;

namespace OasisEditor {

	void EditorExtension::OnAppAwake()
	{
		m_Scene = new Scene();

		m_ViewportWindow = new ViewportWindow(m_Scene);
		m_SceneHierarchyWindow = new SceneHierarchyWindow(m_Scene);
		m_PropertiesWindow = new PropertiesWindow();
		m_ConsoleWindow = new ConsoleWindow();

		Application::Get().GetImGuiExtension().SetBlockEvents(0);

		auto camera = m_Scene->CreateEntity("Camera");
		camera.AddComponent<CameraComponent>(true);

		auto square = m_Scene->CreateEntity("Square");
		auto& squareSpriteRenderer = square.AddComponent<SpriteRendererComponent>();
		squareSpriteRenderer.TexturePath = "C:\\Users\\tudor\\Documents\\CppProjects\\Oasis\\OasisEditor\\assets\\textures\\red.png";

		auto square2 = m_Scene->CreateEntity("Square");
		auto& square2SpriteRenderer = square2.AddComponent<SpriteRendererComponent>();

		ResourceManager::Load<Texture>("C:\\Users\\tudor\\Documents\\CppProjects\\Oasis\\OasisEditor\\assets\\textures\\red.png");

		EventBus::Subscribe(this, &EditorExtension::OnEvent);

		OASIS_LOG_INFO("Extension loaded successfully...");
	}

	void EditorExtension::OnAppUpdate(float deltaTime)
	{
		m_ViewportWindow->OnUpdate(deltaTime);
	}

	void EditorExtension::OnAppRender()
	{
		
	}

	void EditorExtension::OnImGuiRender()
	{
		// Viewport settings
		{
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->GetWorkPos());
				ImGui::SetNextWindowSize(viewport->GetWorkSize());
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", nullptr, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& style = ImGui::GetStyle();
			float minWinSizeX = style.WindowMinSize.x;
			style.WindowMinSize.x = 370.0f;
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			style.WindowMinSize.x = minWinSizeX;
		}

		// Menu
		{
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Close"))
						Application::Get().Close();

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Window"))
				{
					if (ImGui::MenuItem("Viewport"))
						m_ViewportWindow->Show();
					if (ImGui::MenuItem("SceneHierarchy"))
						m_SceneHierarchyWindow->Show();
					if (ImGui::MenuItem("Properties"))
						m_PropertiesWindow->Show();
					if (ImGui::MenuItem("Console"))
						m_ConsoleWindow->Show();

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Runtime"))
				{
					if (ImGui::MenuItem("Play"))
						m_ViewportWindow->PlayGame();
					if (ImGui::MenuItem("Pause"))
						m_ViewportWindow->PauseGame();
					if (ImGui::MenuItem("Stop"))
						m_ViewportWindow->StopGame();

					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}
		}

		m_ViewportWindow->OnImGuiRender();

		m_SceneHierarchyWindow->OnImGuiRender();

		m_PropertiesWindow->SetSelectedEntity(m_SceneHierarchyWindow->GetSelectedEntity());
		m_PropertiesWindow->OnImGuiRender();

		m_ConsoleWindow->OnImGuiRender();

		ImGui::End();
	}

	void EditorExtension::OnAppClose()
	{
	}

	void EditorExtension::OnEvent(Event& e)
	{
		m_ViewportWindow->OnEvent(e);
	}

}