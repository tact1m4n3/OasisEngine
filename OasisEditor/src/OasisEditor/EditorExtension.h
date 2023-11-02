#pragma once

#include <glm/glm.hpp>

#include <Oasis/Oasis.h>

#include <OasisEditor/EditorBuiltinWindows.h>

namespace OasisEditor {

	class EditorExtension : public Oasis::Extension
	{
	private:
		Oasis::Scene* m_Scene;

		ViewportWindow* m_ViewportWindow;
		SceneHierarchyWindow* m_SceneHierarchyWindow;
		PropertiesWindow* m_PropertiesWindow;
		ConsoleWindow* m_ConsoleWindow;
	public:
		virtual void OnAppAwake() override;
		virtual void OnAppUpdate(float deltaTime) override;
		virtual void OnAppRender() override;
		virtual void OnImGuiRender() override;
		virtual void OnAppClose() override;

		inline Oasis::Scene& GetScene() const { return *m_Scene; }
	private:
		void OnEvent(Oasis::Event& e);
	};

}