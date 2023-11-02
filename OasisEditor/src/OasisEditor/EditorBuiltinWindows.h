#pragma once

#include <string>
#include <vector>

#include <Oasis/Oasis.h>

#include <OasisEditor/EditorWindow.h>

namespace OasisEditor {

	class ViewportWindow : public EditorWindow
	{
		Oasis::Scene* m_Scene;
		Oasis::EditorCamera* m_EditorCamera;
		Oasis::Framebuffer* m_ViewportFramebuffer;
		
		glm::vec2 m_ViewportSize;

		bool m_CameraView = false, m_Running = false;
	public:
		ViewportWindow(Oasis::Scene* scene);

		virtual void StylePush() override;
		virtual void StylePop() override;
		virtual void OnContentDraw() override;

		void OnUpdate(float deltaTime);
		void OnEvent(Oasis::Event& e);

		void PlayGame();
		void PauseGame();
		void StopGame();

		inline void SetScene(Oasis::Scene* scene) { m_Scene = scene; }
	};

	class SceneHierarchyWindow : public EditorWindow
	{
	private:
		Oasis::Scene* m_Scene;

		Oasis::Entity m_SelectedEntity;
	public:
		SceneHierarchyWindow(Oasis::Scene* scene);

		virtual void OnContentDraw() override;

		inline Oasis::Entity GetSelectedEntity() const { return m_SelectedEntity; }
	};

	class PropertiesWindow : public EditorWindow
	{
	private:
		Oasis::Entity m_SelectedEntity;
	public:
		PropertiesWindow();

		virtual void OnContentDraw() override;

		inline void SetSelectedEntity(Oasis::Entity entity) { m_SelectedEntity = entity; }
	};

	class ConsoleWindow : public EditorWindow
	{
	private:
		std::vector<std::pair<int, std::string>> m_Messages;
	public:
		ConsoleWindow();

		virtual void OnContentDraw() override;
	private:
		void OnEvent(Oasis::Event& e);
		void OnLogInfoEvent(Oasis::LogInfoEvent& e);
		void OnLogWarnEvent(Oasis::LogWarnEvent& e);
		void OnLogErrorEvent(Oasis::LogErrorEvent& e);
	};

}
