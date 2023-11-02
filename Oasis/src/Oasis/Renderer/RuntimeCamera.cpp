#include <Oasis/Renderer/RuntimeCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {

	RuntimeCamera::RuntimeCamera(bool perspective, float fov, float zoom, float aspect, float near, float far)
		: m_Perspective(perspective), m_Fov(fov), m_Zoom(zoom), m_Aspect(aspect), m_Near(near), m_Far(far)
	{
		CalculateProjection();
	}

	void RuntimeCamera::CalculateProjection()
	{
		if (m_Perspective)
			SetProjection(glm::perspective(m_Fov, m_Aspect, m_Near, m_Far));
		else
			SetProjection(glm::ortho(-m_Aspect * m_Zoom, m_Aspect * m_Zoom, -m_Zoom, m_Zoom, m_Near, m_Far));
	}

}

