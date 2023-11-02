#pragma once

#include <string>

namespace OasisEditor {

	class EditorWindow
	{
	private:
		bool m_Show = true;

		std::string m_Title;
		int m_Flags;
	public:
		EditorWindow(const std::string& title, int flags);
		~EditorWindow() = default;

		void Begin();
		void End();

		void OnImGuiRender();
		
		virtual void StylePush() {}
		virtual void StylePop() {}

		virtual void OnContentDraw() = 0;

		inline void Show() { m_Show = true; }
		inline void Hide() { m_Show = false; }
	};

}
