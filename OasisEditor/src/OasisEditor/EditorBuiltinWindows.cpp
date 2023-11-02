#include <OasisEditor/EditorBuiltinWindows.h>

#include <cstring>
#include <string>

#include <glm/glm.hpp>

#include <imgui.h>

#include <entt.hpp>

#include <OasisEditor/EditorExtension.h>
#include <OasisEditor/WindowGraphics.h>

using namespace Oasis;

namespace OasisEditor {

	template<typename T, typename FuncType>
	void DrawComponent(const std::string& componentName, Entity entity, FuncType function);

	ViewportWindow::ViewportWindow(Oasis::Scene* scene)
		: EditorWindow("Viewport", ImGuiWindowFlags_MenuBar), m_Scene(scene), m_EditorCamera(new EditorCamera()), m_ViewportFramebuffer(new Framebuffer(1, 1))
	{
	}

	void ViewportWindow::StylePush()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	}

	void ViewportWindow::StylePop()
	{
		ImGui::PopStyleVar();
	}

	void ViewportWindow::OnContentDraw()
	{
		if (!ImGui::IsWindowHovered())
		{
			m_EditorCamera->SetBlockMouseEvents(1);
		}
		else
		{
			m_EditorCamera->SetBlockMouseEvents(0);
		}

		if (!ImGui::IsWindowFocused())
		{
			Application::Get().GetImGuiExtension().SetBlockEvents(1);

			m_EditorCamera->ResetInput();
		}
		else
		{
			Application::Get().GetImGuiExtension().SetBlockEvents(0);
		}

		ImVec2 viewportWindowSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize.x != viewportWindowSize.x || m_ViewportSize.y != viewportWindowSize.y)
		{
			m_ViewportSize = { viewportWindowSize.x, viewportWindowSize.y };
			m_ViewportFramebuffer->Resize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
			m_EditorCamera->ResizeViewport((int)m_ViewportSize.x, (int)m_ViewportSize.y);
		}

		{
			if (ImGui::BeginMenuBar())
			{
				WindowGraphics::DrawBoolControl("CameraView", m_CameraView);

				ImGui::EndMenuBar();
			}
		}

		{
			m_ViewportFramebuffer->Bind();
			m_ViewportFramebuffer->Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

			if (m_CameraView)
			{
				m_Scene->OnRenderRuntime(m_ViewportSize.x / m_ViewportSize.y);
			}
			else
			{
				m_Scene->OnRenderEditor(m_EditorCamera);
			}

			m_ViewportFramebuffer->Unbind();
		}

		ImGui::Image((void*)(m_ViewportFramebuffer->GetColorAttachment()->GetRendererId()), viewportWindowSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	}

	void ViewportWindow::OnUpdate(float deltaTime)
	{
		if (m_Running)
		{
			m_Scene->OnUpdateRuntime(deltaTime);
			if (!m_CameraView)
				m_EditorCamera->OnUpdate(deltaTime);
		}
		else
		{
			m_EditorCamera->OnUpdate(deltaTime);
		}
	}

	void ViewportWindow::OnEvent(Event& e)
	{
		if (m_CameraView)
		{
			// scene on event runtime
		}
		else
		{
			m_EditorCamera->OnEvent(e);
		}
	}

	void ViewportWindow::PlayGame()
	{
		m_CameraView = true;
		m_Running = true;
	}

	void ViewportWindow::PauseGame()
	{
		m_Running = false;
	}

	void ViewportWindow::StopGame()
	{
		m_CameraView = false;
		m_Running = false;
		// reset scene
	}

	SceneHierarchyWindow::SceneHierarchyWindow(Scene* scene)
		: EditorWindow("SceneHierarchy", ImGuiWindowFlags_None), m_Scene(scene)
	{
	}

	void SceneHierarchyWindow::OnContentDraw()
	{
		m_Scene->GetRegistry().each([&](entt::entity entityId) {
			Entity entity(entityId, m_Scene);
			std::string& name = entity.GetComponent<NameComponent>().Name;

			ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
			flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
			bool open = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());

			if (ImGui::IsItemClicked())
			{
				m_SelectedEntity = entity;
			}

			bool entityDeleted = false;
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					entityDeleted = true;
				}

				ImGui::EndPopup();
			}

			if (open)
			{
				ImGui::TreePop();
			}

			if (entityDeleted)
			{
				m_Scene->DestroyEntity(entity);
				if (m_SelectedEntity == entity)
					m_SelectedEntity = { };
			}
		});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_SelectedEntity = { };
		}

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Scene->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}
	}

	PropertiesWindow::PropertiesWindow()
		: EditorWindow("Properties", ImGuiWindowFlags_None)
	{
	}

	void PropertiesWindow::OnContentDraw()
	{
		if (!m_SelectedEntity)
			return;

		{
			std::string& name = m_SelectedEntity.GetComponent<NameComponent>().Name;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			memcpy(buffer, name.c_str(), name.size());

			if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
			{
				name = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponentPopup");
		}

		if (ImGui::BeginPopup("AddComponentPopup"))
		{
			if (ImGui::MenuItem("Transform Component"))
			{
				if (!m_SelectedEntity.HasComponent<TransformComponent>())
					m_SelectedEntity.AddComponent<TransformComponent>();
				else
					OASIS_LOG_WARN("Entity already has a transform component...");
			}
			if (ImGui::MenuItem("Sprite Renderer Component"))
			{
				if (!m_SelectedEntity.HasComponent<SpriteRendererComponent>())
					m_SelectedEntity.AddComponent<SpriteRendererComponent>();
				else
					OASIS_LOG_WARN("Entity already has a sprite renderer component...");
			}
			if (ImGui::MenuItem("Camera Component"))
			{
				if (!m_SelectedEntity.HasComponent<CameraComponent>())
					m_SelectedEntity.AddComponent<CameraComponent>(false);
				else
					OASIS_LOG_WARN("Entity already has a camera component...");
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		if (m_SelectedEntity.HasComponent<TransformComponent>())
		{
			DrawComponent<TransformComponent>("Transform Component", m_SelectedEntity, [](auto& component)
				{
					WindowGraphics::DrawVec3Control("Position", component.Position);
					WindowGraphics::DrawVec3Control("Rotation", component.Rotation);
					WindowGraphics::DrawVec3Control("Scale", component.Scale, 1.0f);
				});
		}

		if (m_SelectedEntity.HasComponent<SpriteRendererComponent>())
		{
			DrawComponent<SpriteRendererComponent>("Sprite Renderer Component", m_SelectedEntity, [](auto& component)
				{
					WindowGraphics::DrawColorControl("Color", component.Color);
					WindowGraphics::DrawTextureControl("Texture", component.TexturePath);
				});
		}

		if (m_SelectedEntity.HasComponent<CameraComponent>())
		{
			DrawComponent<CameraComponent>("Camera Component", m_SelectedEntity, [](auto& component)
				{
					WindowGraphics::DrawBoolControl("Main", component.Main);

					bool perspective = component.CameraInstance->GetPerspective();
					WindowGraphics::DrawBoolControl("Perspective", perspective);
					component.CameraInstance->SetPerspective(perspective);

					component.CameraInstance->CalculateProjection();
				});
		}
	}

	template<typename T, typename FuncType>
	static void DrawComponent(const std::string& componentName, Entity entity, FuncType function)
	{
		ImGui::Separator();

		ImGui::AlignTextToFramePadding();

		bool open = ImGui::TreeNodeEx(componentName.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

		bool componentDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Remove Component"))
			{
				componentDeleted = true;
			}

			ImGui::EndPopup();
		}

		if (open)
		{
			function(entity.GetComponent<T>());
			ImGui::TreePop();
		}

		if (componentDeleted)
		{
			entity.RemoveComponent<T>();
		}
	}

	ConsoleWindow::ConsoleWindow()
		: EditorWindow("Console", ImGuiWindowFlags_None)
	{
		EventBus::Subscribe(this, &ConsoleWindow::OnEvent);
	}

	void ConsoleWindow::OnContentDraw()
	{
		{
			if (ImGui::Button("Clear"))
			{
				m_Messages.clear();
			}
		}

		ImGui::Separator();

		{
			ImGui::BeginChild("scrolling");
			for (auto [t, msg] : m_Messages)
			{
				if (t == 0)
					ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 1.0f, 1.0f, 1.0f });
				if (t == 1)
					ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 1.0f, 0.0f, 1.0f });
				if (t == 2)
					ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.0f, 0.0f, 1.0f });

				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
				ImGui::Text(msg.c_str());
				ImGui::PopStyleVar();

				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
		}
	}

	void ConsoleWindow::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Subscribe(this, &ConsoleWindow::OnLogInfoEvent);
		dispatcher.Subscribe(this, &ConsoleWindow::OnLogWarnEvent);
		dispatcher.Subscribe(this, &ConsoleWindow::OnLogErrorEvent);
	}

	void ConsoleWindow::OnLogInfoEvent(LogInfoEvent& e)
	{
		m_Messages.push_back({ 0, e.GetMessage() });
	}

	void ConsoleWindow::OnLogWarnEvent(LogWarnEvent& e)
	{
		m_Messages.push_back({ 1, e.GetMessage() });
	}

	void ConsoleWindow::OnLogErrorEvent(LogErrorEvent& e)
	{
		m_Messages.push_back({ 2, e.GetMessage() });
	}

}