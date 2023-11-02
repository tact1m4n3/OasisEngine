#pragma once

#include <Oasis/Renderer/Camera.h>

namespace Oasis {

	class RuntimeCamera : public Camera
	{
	private:
		bool m_Perspective;

		float m_Fov;
		float m_Zoom;
		float m_Aspect;
		float m_Near;
		float m_Far;
	public:
		RuntimeCamera(bool perspective = true, float fov = 45.0f, float m_Zoom = 1.0f, float aspect = 1.0f, float near = 0.1f, float far = 1000.0f);
		~RuntimeCamera() = default;

		virtual void CalculateProjection() override;

		void SetFov(float fov) { m_Fov = fov; }
		float GetFov() const { return m_Fov; }

		void SetAspect(float aspect) { m_Aspect = aspect; }
		float GetAspect() const { return m_Aspect; }

		void SetNearPlane(float near) { m_Near = near; }
		float GetNearPlane() const { return m_Near; }
		
		void SetFarPlane(float far) { m_Far = far; }
		float GetFarPlane() const { return m_Far; }

		void SetPerspective(bool perspective) { m_Perspective = perspective; }
		bool GetPerspective() const { return m_Perspective; }
	};

}
