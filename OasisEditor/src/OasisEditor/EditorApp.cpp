#include <iostream>

#include <imgui.h>
#include <glm/glm.hpp>
#include <entt.hpp>

#include <Oasis/Oasis.h>

#include "EditorExtension.h"

using namespace Oasis;

namespace OasisEditor {

	class EditorApp : public Application
	{
	public:
		EditorApp()
			: Application("EditorApp", 1400, 1000)
		{
			SubmitExtension(new EditorExtension());
		}
	};

}

Application* CreateApplication()
{
	return new OasisEditor::EditorApp();
}