#include "Camera.h"

namespace RenderToy
{
	Camera::Camera(float windowWidth, float windowHeight)
	{
		float aspectRatio = windowWidth / windowHeight;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, nearPlane, farPlane);

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	glm::mat4 Camera::GenerateMVPMatrix(glm::vec3 position, float rotation, glm::vec3 pointOfRotation)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotation), pointOfRotation);
		model = glm::translate(model, position);

		return m_Projection * m_View * model;
	}

	glm::vec3 Camera::GetPosition()
	{
		return m_Position;
	}

	void Camera::SetPosition(glm::vec3 newPosition)
	{
		m_Position = newPosition;
		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::IncreasePosition(glm::vec3 increaseBy)
	{
		m_Position += increaseBy;
		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::SetAspectRatio(float width, float height)
	{
		float aspectRatio = width / height;
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		m_Projection = glm::perspective(glm::radians(m_Fov), aspectRatio, nearPlane, farPlane);
	}

	Camera::~Camera()
	{

	}
}