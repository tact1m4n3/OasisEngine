#pragma once

#include <string>

#include <glm/glm.hpp>

struct GLFWwindow;

namespace Oasis {

	class Window
	{
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			int Width;
			int Height;
		};

		WindowData m_Data;

		static int s_WindowCount;
	public:
		Window(const std::string& title, int width, int height);

		void OnUpdate();
		void Close();

		void Clear(const glm::vec4& color);

		void ActivateContext();
		void SetVSync(int enabled);
		void SetViewport(int width, int height);

		inline GLFWwindow* GetNativeWindow() const { return m_Window; }
		inline int GetWidth() const { return m_Data.Width; }
		inline int GetHeight() const { return m_Data.Height; }
		inline float GetAspectRatio() const { return (float)m_Data.Width / (float)m_Data.Height; }
	};

}

