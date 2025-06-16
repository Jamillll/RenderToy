#include "Camera.h"

namespace RenderToy
{
	Camera::Camera(float windowWidth, float windowHeight)
	{
		m_AspectRatio = windowWidth / windowHeight;
		float nearPlane = 0.1f;
		float farPlane = 500.0f;
		m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, nearPlane, farPlane);

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	glm::mat4 Camera::GenerateMVPMatrix(TransformData transform)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.Position);
		model = glm::rotate(model, glm::radians(transform.Rotation), transform.PointOfRotation);
		model = glm::scale(model, transform.Scale);

		return m_Projection * m_View * model;
	}

	glm::vec3 Camera::GetPosition()
	{
		return m_Position;
	}

	glm::vec3 Camera::GetFront()
	{
		return m_Front;
	}

	glm::vec3 Camera::GetUp()
	{
		return m_Up;
	}

	float Camera::GetFov()
	{
		return m_Fov;
	}

	void Camera::SetFov(float fov)
	{
		m_Fov = fov;

		float nearPlane = 0.1f;
		float farPlane = 500.0f;
		m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, nearPlane, farPlane);
	}

	void Camera::SetPosition(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	{
		m_Position = position;
		m_Front = front;
		m_Up = up;

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::IncreasePosition(glm::vec3 increaseBy)
	{
		m_Position += increaseBy;
		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::SetAspectRatio(float width, float height)
	{
		float m_AspectRatio = width / height;
		float nearPlane = 0.1f;
		float farPlane = 500.0f;
		m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, nearPlane, farPlane);
	}

	Camera::~Camera()
	{

	}

	TransformData::TransformData(glm::vec3 position, glm::vec3 scale, float rotation, glm::vec3 pointOfRotation)
		: Position(position), Scale(scale), Rotation(rotation), PointOfRotation(pointOfRotation) {}
}