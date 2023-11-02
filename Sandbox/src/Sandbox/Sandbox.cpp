#include <iostream>

#include <imgui.h>
#include <glm/glm.hpp>
#include <entt.hpp>

#include <Oasis/Oasis.h>

using namespace Oasis;

class MyExtension : public Extension
{
private:
	float m_DeltaTime;
	OrthographicCamera* m_Camera;
public:
	virtual void OnAppAwake() override
	{
		m_DeltaTime = 0.0f;
		m_Camera = new OrthographicCamera(-Application::Get().GetWindow().GetAspectRatio(), Application::Get().GetWindow().GetAspectRatio(), -1.0f, 1.0f);

		Application::Get().GetEventBus().Subscribe(this, &MyExtension::OnEvent);
	}

	virtual void OnAppUpdate(float deltaTime) override
	{
		m_DeltaTime = deltaTime;
	}

	virtual void OnAppRender() override
	{
		Application::Get().GetRenderer2D().Begin(m_Camera);
		Application::Get().GetRenderer2D().DrawSprite({ 0.0f, 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		Application::Get().GetRenderer2D().End();
	}

	virtual void OnImGuiRender() override
	{
		bool open = true;

		ImGui::Begin("Performance", &open);
		ImGui::Text("FPS: %d", (int)(1 / m_DeltaTime));
		ImGui::End();
	}

	void OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Subscribe(this, &MyExtension::OnWindowResizeEvent);
	}

	void OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_Camera->SetProjection(-Application::Get().GetWindow().GetAspectRatio(), Application::Get().GetWindow().GetAspectRatio(), -1.0f, 1.0f);
	}
};

class SandboxApp : public Application
{
public:
	SandboxApp()
		: Application("SandboxApp", 800, 600)
	{
		SubmitExtension(new MyExtension());
	}
};

Application* CreateApplication()
{
	return new SandboxApp();
}
