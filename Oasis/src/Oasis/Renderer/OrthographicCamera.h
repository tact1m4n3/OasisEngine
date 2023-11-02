#pragma once

#include <glm/glm.hpp>

namespace Oasis {

    class OrthographicCamera
    {
    private:
        glm::vec3 m_Position;
        float m_Rotation;

        float m_Left, m_Right, m_Bottom, m_Top;
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        virtual ~OrthographicCamera() = default;

        void SetProjection(float left, float right, float bottom, float top);

        glm::mat4 GetProjectionMatrix();
        glm::mat4 GetViewMatrix();

        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline void SetPosition(const glm::vec3& position) { m_Position = position; }

        inline float GetRotation() const { return m_Rotation; }
        inline void SetRotation(float rotation) { m_Rotation = rotation; }
    };

}