#include <Oasis/Core/Application.h>

#include <GLFW/glfw3.h>

#include <Oasis/Debug/Log.h>
#include <Oasis/Debug/Assert.h>
#include <Oasis/Renderer/Renderer2D.h>
#include <Oasis/Events/EventBus.h>
#include <Oasis/Events/EventDispatcher.h>
#include <Oasis/Resources/ResourceManager.h>

namespace Oasis {

	Application* Application::s_AppInstance = nullptr;

	Application::Application(const std::string& name, int appWidth, int appHeight)
		: m_Name(name)
	{
		OASIS_ASSERT(!s_AppInstance, "Can't create two instances of application...");
		s_AppInstance = this;
		
		Log::Init();
		ResourceManager::Init();

		m_Window = new Window(m_Name, appWidth, appHeight);
		m_Window->SetVSync(1);

		EventBus::Subscribe(this, &Application::OnEvent);

		m_ImGuiExtension = new ImGuiExtension();
		
		Renderer2D::Init();
	}

	Application::~Application()
	{
		Renderer2D::Init();

		delete m_Window;

		ResourceManager::Shutdown();
		Log::Shutdown();
	}

	void Application::Run()
	{
		{
			AppAwakeEvent appAwakeEvent;
			EventBus::Send(appAwakeEvent);
		
			m_ImGuiExtension->OnAppAwake();
	
			for (auto* extension : m_ExtensionList)
				extension->OnAppAwake();
		}

		m_Running = true;
		m_LastTime = (float)glfwGetTime();
		while (m_Running)
		{
			m_Window->Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

			float deltaTime = (float)glfwGetTime() - m_LastTime;
			m_LastTime = (float)glfwGetTime();

			{
				AppUpdateEvent appRenderEvent(deltaTime);
				EventBus::Send(appRenderEvent);

				for (auto* extension : m_ExtensionList)
					extension->OnAppRender();
			}

			{
				AppRenderEvent appUpdateEvent;
				EventBus::Send(appUpdateEvent);

				for (auto* extension : m_ExtensionList)
					extension->OnAppUpdate(deltaTime);
			}
			
			{
				m_ImGuiExtension->Begin();

				ImGuiRenderEvent imGuiRenderEvent;
				EventBus::Send(imGuiRenderEvent);

				for (auto* extension : m_ExtensionList)
					extension->OnImGuiRender();

				m_ImGuiExtension->End();
			}

			m_Window->OnUpdate();
		}

		{
			AppCloseEvent appCloseEvent;
			EventBus::Send(appCloseEvent);

			m_ImGuiExtension->OnAppClose();

			for (auto* extension : m_ExtensionList)
				extension->OnAppClose();
		}

		m_Window->Close();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::SubmitExtension(Extension* extension)
	{
		m_ExtensionList.push_front(extension);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Subscribe(this, &Application::WindowCloseCallback);
	}

	void Application::WindowCloseCallback(WindowCloseEvent& e)
	{
		m_Running = false;
	}

}

