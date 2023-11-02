#pragma once

#include <glm/glm.hpp>

#include <Oasis/Events/Event.h>
#include <Oasis/Renderer/Camera.h>

namespace Oasis {

	class EditorCamera : public Camera
	{
	private:
		float m_MovementSpeed;
		float m_ScrollSpeed;
		float m_Fov;
		float m_ViewportAspect;
		float m_Near;
		float m_Far;
		
		bool m_WPressed = false, m_SPressed = false, m_APressed = false, m_DPressed = false;
		float m_ScrollYOffset = 0.0f;
		
		glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };


		bool m_MouseEventsBlocked = false;
	public:
		EditorCamera(float movementSpeed = 3.0f, float scrollSpeed = 5.0f, float fov = 45.0f, float viewportAspect = 1.0f, float near = 0.1f, float far = 1000.0f);
		~EditorCamera() = default;

		virtual void CalculateProjection() override;
		glm::mat4 GetCameraTransformation();

		void OnUpdate(float deltaTime);

		void OnEvent(Event& e);

		void ResetInput();
		void ResizeViewport(int width, int height);

		inline void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
		inline void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }
		inline void SetBlockMouseEvents(bool status) { m_MouseEventsBlocked = status; }
	private:
		void OnKeyPressedEvent(KeyPressedEvent& e);
		void OnKeyReleasedEvent(KeyReleasedEvent& e);
		void OnMouseScrolledEvent(MouseScrolledEvent& e);
	};
	
}

