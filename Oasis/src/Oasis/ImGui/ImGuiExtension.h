#pragma once

#include <Oasis/Core/Extension.h>
#include <Oasis/Events/Event.h>

namespace Oasis {

	class ImGuiExtension : public Extension
	{
	private:
		bool m_BlockEvents;
	public:
		virtual void OnAppAwake() override;

		virtual void Begin();
		virtual void End();
		
		virtual void OnAppClose() override;

		inline void SetBlockEvents(bool blocked) { m_BlockEvents = blocked; }
	private:
		void OnEvent(Event& e);
	};

}
