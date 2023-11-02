#pragma once

#include <glm/glm.hpp>

namespace Oasis {

	class Camera
	{
	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	public:
		virtual void CalculateProjection() = 0;

		inline const glm::mat4& GetProjection() const { return m_Projection; }
	protected:
		inline void SetProjection(const glm::mat4& proj) { m_Projection = proj; }
	};

}
