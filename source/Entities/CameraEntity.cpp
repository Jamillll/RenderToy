#include "CameraEntity.h"

namespace RenderToy
{
    CameraEntity::CameraEntity(Camera* camera)
        : m_Camera(camera) {
    }

    void CameraEntity::CameraInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            Position.y += Speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            Position.y -= Speed;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Position += Front * Speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Position -= Front * Speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Position -= glm::normalize(glm::cross(Front, Up)) * Speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Position += glm::normalize(glm::cross(Front, Up)) * Speed;

        double xPosition = 0.0f;
        double yPosition = 0.0f;

        glfwGetCursorPos(window, &xPosition, &yPosition);

        float xOffset = (float)xPosition - LastXPosition;
        float yOffset = LastYPosition - (float)yPosition; // reversed since y-coordinates go from bottom to top
        LastXPosition = (float)xPosition;
        LastYPosition = (float)yPosition;

        xOffset *= Sensitivity;
        yOffset *= Sensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        UpdateCameraPosition();
    }

    void CameraEntity::UpdateCameraPosition()
    {
        m_Camera->SetPosition(Position, Front, Up);
        m_Camera->SetFov(Fov);
    }

    CameraEntity::~CameraEntity() {}
}