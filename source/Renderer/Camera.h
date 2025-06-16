#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace RenderToy
{
	struct TransformData
	{
		glm::vec3 Position;
		glm::vec3 Scale;
		float Rotation;
		glm::vec3 PointOfRotation;

		TransformData(
			glm::vec3 position = {0, 0, 0},
			glm::vec3 scale = {1, 1, 1},
			float rotation = 0,
			glm::vec3 pointOfRotation = {0, 0, 1});
	};

	class Camera
	{
	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 100.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_Fov = 65.0f;

		float m_AspectRatio;

		glm::mat4 m_View, m_Projection;

	public:
		Camera(float windowWidth, float windowHeight);

		glm::mat4 GenerateMVPMatrix(TransformData transform);

		void SetPosition(
			glm::vec3 position, 
			glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), 
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
		
		glm::vec3 GetPosition();
		glm::vec3 GetFront();
		glm::vec3 GetUp();

		float GetFov();
		void SetFov(float fov);

		void IncreasePosition(glm::vec3 increaseBy);

		void SetAspectRatio(float width, float height);

		~Camera();
	};
}