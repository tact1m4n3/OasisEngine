#include <Oasis/Core/Window.h>

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Oasis/Debug/Assert.h>
#include <Oasis/Events/EventBus.h>

namespace Oasis {

	int Window::s_WindowCount = 0;

	Window::Window(const std::string& title, int width, int height)
		: m_Data({ title, width, height })
	{
		if (s_WindowCount <= 0)
		{
			int success = glfwInit();
			OASIS_ASSERT(success, "Failed to initialize GLFW...");
		}

		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_WindowCount;

			OASIS_ASSERT(m_Window, "Failed to create glfw window...");
		}

		{
			glfwMakeContextCurrent(m_Window);
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			OASIS_ASSERT(status, "Failed to initialize glad...");
		}

		glfwSwapInterval(0);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent e;
				EventBus::Send(e);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				glViewport(0, 0, width, height);

				WindowResizeEvent e(width, height);
				EventBus::Send(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int keycode, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (action == GLFW_PRESS)
				{
					KeyPressedEvent e((KeyCode)keycode, 0);
					EventBus::Send(e);
				}
				else if (action == GLFW_REPEAT)
				{
					KeyPressedEvent e((KeyCode)keycode, 1);
					EventBus::Send(e);
				}
				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent e((KeyCode)keycode);
					EventBus::Send(e);
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int charcode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent e((char)charcode);
				EventBus::Send(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent e((MouseCode)button);
					EventBus::Send(e);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleasedEvent e((MouseCode)button);
					EventBus::Send(e);
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double posX, double posY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent e((float)posX, (float)posY);
				EventBus::Send(e);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent e((float)offsetX, (float)offsetY);
				EventBus::Send(e);
			});


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, m_Data.Width, m_Data.Height);

		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Close()
	{
		glfwDestroyWindow(m_Window);
		--s_WindowCount;

		if (s_WindowCount <= 0)
			glfwTerminate();
	}

	void Window::Clear(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::ActivateContext()
	{
		glfwMakeContextCurrent(m_Window);
	}

	void Window::SetVSync(int enabled)
	{
		glfwSwapInterval(enabled);
	}

	void Window::SetViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

}