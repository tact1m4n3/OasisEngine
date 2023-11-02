#include <Oasis/Renderer/OrthographicCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_Position(0.0f, 0.0f, 0.0f), m_Rotation(0.0f), m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
    {
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_Left = left;
        m_Right = right;
        m_Bottom = bottom;
        m_Top = top;
    }

    glm::mat4 OrthographicCamera::GetProjectionMatrix()
    {
        return glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
    }

    glm::mat4 OrthographicCamera::GetViewMatrix()
    {
        return glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f)));
    }

}