#pragma once

#include <string>
#include <list>

#include <Oasis/Core/Window.h>
#include <Oasis/Core/Extension.h>
#include <Oasis/Events/Event.h>
#include <Oasis/ImGui/ImGuiExtension.h>

namespace Oasis {

    class Application
    {
    private:
        static Application* s_AppInstance;

        std::string m_Name;

        Window* m_Window;
        ImGuiExtension* m_ImGuiExtension;
        std::list<Extension*> m_ExtensionList;

        bool m_Running;
        float m_LastTime;
    public:
        Application(const std::string& name, int appWidth, int appHeight);
        ~Application();

        void Run();
        void Close();

        void SubmitExtension(Extension* extension);

        inline Window& GetWindow() const { return *m_Window; }
        inline ImGuiExtension& GetImGuiExtension() const { return *m_ImGuiExtension; }
        inline static Application& Get() { return *s_AppInstance; }
    private:
        void OnEvent(Event& e);
        void WindowCloseCallback(WindowCloseEvent& e);
    };

}