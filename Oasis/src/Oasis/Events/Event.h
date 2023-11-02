#pragma once

#include <string>

#include <Oasis/Core/KeyCodes.h>
#include <Oasis/Core/MouseCodes.h>

namespace Oasis {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		LogInfo, LogWarn, LogError,
		AppAwake, AppUpdate, AppRender, ImGuiRender, AppClose,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		UserImplemented
	};

	enum EventCategory
	{
		EventCategoryNone = 0,
		EventCategoryApplication = (1 << 0),
		EventCategoryDebug = (1 << 1),
		EventCategoryInput = (1 << 2),
		EventCategoryKeyboard = (1 << 3),
		EventCategoryMouse = (1 << 4),
		EventCategoryMouseButton = (1 << 5),
		EventCategoryUser = (1 << 6)
	};
	
#define OASIS_EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define OASIS_EVENT_CLASS_CATEGORY(category) virtual int GetEventCategory() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual int GetEventCategory() const = 0;
		virtual const char* GetName() const = 0;

		bool IsInCategory(EventCategory category)
		{
			return GetEventCategory() & category;
		}
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		OASIS_EVENT_CLASS_TYPE(WindowClose)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizeEvent : public Event
	{
	private:
		int m_Width, m_Height;
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{
		}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		OASIS_EVENT_CLASS_TYPE(WindowResize)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LogInfoEvent : public Event
	{
	private:
		std::string m_Msg;
	public:
		LogInfoEvent(const std::string& msg)
			: m_Msg(msg)
		{
		}

		inline const std::string& GetMessage() const { return m_Msg; }

		OASIS_EVENT_CLASS_TYPE(LogInfo)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryDebug)
	};

	class LogWarnEvent : public Event
	{
	private:
		std::string m_Msg;
	public:
		LogWarnEvent(const std::string& msg)
			: m_Msg(msg)
		{
		}

		inline const std::string& GetMessage() const { return m_Msg; }

		OASIS_EVENT_CLASS_TYPE(LogWarn)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryDebug)
	};

	class LogErrorEvent : public Event
	{
	private:
		std::string m_Msg;
	public:
		LogErrorEvent(const std::string& msg)
			: m_Msg(msg)
		{
		}

		inline const std::string& GetMessage() const { return m_Msg; }

		OASIS_EVENT_CLASS_TYPE(LogError)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryDebug)
	};

	class AppAwakeEvent : public Event
	{
	public:
		AppAwakeEvent()
		{
		}

		OASIS_EVENT_CLASS_TYPE(AppAwake)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	private:
		float m_DeltaTime;
	public:
		AppUpdateEvent(float deltaTime)
			: m_DeltaTime(deltaTime)
		{
		}

		inline float GetDeltaTime() const { return m_DeltaTime; }

		OASIS_EVENT_CLASS_TYPE(AppUpdate)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent()
		{
		}

		OASIS_EVENT_CLASS_TYPE(AppRender)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ImGuiRenderEvent : public Event
	{
	public:
		ImGuiRenderEvent()
		{
		}

		OASIS_EVENT_CLASS_TYPE(ImGuiRender)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppCloseEvent : public Event
	{
	public:
		AppCloseEvent()
		{
		}

		OASIS_EVENT_CLASS_TYPE(AppClose)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

		OASIS_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		OASIS_EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		OASIS_EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public Event
	{
	private:
		char m_Character;
	public:
		KeyTypedEvent(char c)
			: m_Character(c)
		{
		}

		inline char GetCharacter() const { return m_Character; }

		OASIS_EVENT_CLASS_TYPE(KeyTyped)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	};

	class MouseMovedEvent : public Event
	{
	private:
		float m_MouseX, m_MouseY;
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y)
		{
		}

		inline float GetMouseX() const { return m_MouseX; }
		inline float GetMouseY() const { return m_MouseY; }

		OASIS_EVENT_CLASS_TYPE(MouseMoved)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	};

	class MouseScrolledEvent : public Event
	{
	private:
		float m_OffsetX, m_OffsetY;
	public:
		MouseScrolledEvent(float offsetX, float offsetY)
			: m_OffsetX(offsetX), m_OffsetY(offsetY)
		{
		}

		inline float GetOffsetX() const { return m_OffsetX; }
		inline float GetOffsetY() const { return m_OffsetY; }

		OASIS_EVENT_CLASS_TYPE(MouseScrolled)
		OASIS_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	};

	class MouseButtonEvent : public Event
	{
	private:
		MouseCode m_Button;
	public:
		MouseButtonEvent(MouseCode button)
			: m_Button(button)
		{
		}

		inline MouseCode GetMouseButton() const { return m_Button; }

		OASIS_EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button)
		{
		}
		
		OASIS_EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button)
		{
		}

		OASIS_EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
