#include <Oasis/Renderer/EditorCamera.h>

#include <glm/gtc/matrix_transform.hpp>

#include <Oasis/Core/Application.h>
#include <Oasis/Core/KeyCodes.h>
#include <Oasis/Events/EventDispatcher.h>

namespace Oasis {
	
	EditorCamera::EditorCamera(float movementSpeed, float scrollSpeed, float fov, float viewportAspect, float near, float far)
		: m_MovementSpeed(movementSpeed), m_ScrollSpeed(scrollSpeed), m_Fov(fov), m_ViewportAspect(viewportAspect), m_Near(near), m_Far(far)
	{
	}

	void EditorCamera::CalculateProjection()
	{
		SetProjection(glm::perspective(m_Fov, m_ViewportAspect, m_Near, m_Far));
	}

	glm::mat4 EditorCamera::GetCameraTransformation()
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		return glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * rotation);
	}

	void EditorCamera::OnUpdate(float deltaTime)
	{
		if (m_WPressed)
			m_Position.y += m_MovementSpeed * deltaTime;
		if (m_SPressed)
			m_Position.y -= m_MovementSpeed * deltaTime;
		if (m_APressed)
			m_Position.x -= m_MovementSpeed * deltaTime;
		if (m_DPressed)
			m_Position.x += m_MovementSpeed * deltaTime;

		if (!m_MouseEventsBlocked)
			m_Position.z -= m_ScrollSpeed * m_ScrollYOffset * deltaTime;
		
		CalculateProjection();

		m_ScrollYOffset = 0.0f;
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Subscribe(this, &EditorCamera::OnKeyPressedEvent);
		dispatcher.Subscribe(this, &EditorCamera::OnKeyReleasedEvent);
		dispatcher.Subscribe(this, &EditorCamera::OnMouseScrolledEvent);
	}

	void EditorCamera::ResetInput()
	{
		m_WPressed = false;
		m_SPressed = false;
		m_APressed = false;
		m_DPressed = false;
	}

	void EditorCamera::ResizeViewport(int width, int height)
	{
		m_ViewportAspect = (float)width / (float)height;

		CalculateProjection();
	}

	void EditorCamera::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == KeyCode::W)
			m_WPressed = true;
		else if (e.GetKeyCode() == KeyCode::S)
			m_SPressed = true;
		else if (e.GetKeyCode() == KeyCode::A)
			m_APressed = true;
		else if (e.GetKeyCode() == KeyCode::D)
			m_DPressed = true;
	}

	void EditorCamera::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == KeyCode::W)
			m_WPressed = false;
		else if (e.GetKeyCode() == KeyCode::S)
			m_SPressed = false;
		else if (e.GetKeyCode() == KeyCode::A)
			m_APressed = false;
		else if (e.GetKeyCode() == KeyCode::D)
			m_DPressed = false;
	}

	void EditorCamera::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_ScrollYOffset += e.GetOffsetY();
	}

}
