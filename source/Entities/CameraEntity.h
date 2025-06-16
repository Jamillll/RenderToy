#pragma once
#include "EntityManager.h"
#include "../Assets/AssetManager.h"
#include "../Renderer/Camera.h"

namespace RenderToy
{
	class CameraEntity : public Entity
	{
	private:
		Camera* m_Camera = nullptr;

	public:
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 100.0f);
		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		float Fov = 65.0f;

		CameraEntity(Camera* camera);
		void UpdateCameraPosition();
		~CameraEntity();
	};
}