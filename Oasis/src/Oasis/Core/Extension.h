#pragma once

#include <Oasis/Events/Event.h>
#include <Oasis/Events/EventBus.h>

namespace Oasis {

    class Extension
    {
    public:
        virtual void OnAppAwake() {}
        virtual void OnAppUpdate(float deltaTime) {}
        virtual void OnAppRender() {}
        virtual void OnImGuiRender() {}
        virtual void OnAppClose() {}
    };

}
