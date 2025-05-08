#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RenderToy
{
	class Camera
	{
	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 100.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_Fov = 65.0f;

		glm::mat4 m_View, m_Projection;

	public:
		Camera(float windowWidth, float windowHeight);

		glm::mat4 GenerateMVPMatrix(glm::vec3 position, float rotation = 0, glm::vec3 pointOfRotation = glm::vec3(0.0, 0.0, 1.0));

		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 position);
		void IncreasePosition(glm::vec3 increaseBy);

		void SetAspectRatio(float width, float height);

		~Camera();
	};
}