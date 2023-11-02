#include <Oasis/ImGui/ImGuiExtension.h>

#include <iostream>

#include <GLFW/glfw3.h>

#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include <Oasis/Core/Application.h>
#include <Oasis/Core/KeyCodes.h>
#include <Oasis/Events/EventBus.h>

namespace Oasis {

    static void SetThemeColors()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        
    }

	void ImGuiExtension::OnAppAwake()
	{
        m_BlockEvents = true;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        io.Fonts->AddFontFromFileTTF("internal/assets/fonts/SegoeUI.ttf", 18.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("internal/assets/fonts/SegoeUI.ttf", 18.0f);

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetThemeColors();

        ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().GetNativeWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 410");

        EventBus::Subscribe(this, &ImGuiExtension::OnEvent);
	}

    void ImGuiExtension::Begin()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)Application::Get().GetWindow().GetWidth(), (float)Application::Get().GetWindow().GetHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiExtension::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupContextCurrent = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContextCurrent);
        }
    }

    void ImGuiExtension::OnAppClose()
    {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiExtension::OnEvent(Event& e)
    {
        if (m_BlockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();
            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
    }
    
}
