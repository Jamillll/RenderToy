#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "Entities/EntityManager.h"

// TEMP
//#include "Assets/Texture.h"

namespace RenderToy
{
	struct ApplicationState
	{
		bool showDemoWindow = false;
		bool SceneViewCaptured = false;
	};

	class Application
	{
	private:
		bool m_Running;
		GLFWwindow* m_Window = nullptr;
		ApplicationState m_State;

	public:
		Application();

		void Run();

		~Application();

	private:
		void SceneView();
		void AssetTray(void* texture, AssetHandle* assetSelected, bool* isEntity);
		void SceneHierarchy(EntityHandle* entitySelected, bool* isEntity);

		void Properties(unsigned int handleSelected, bool isEntity);
		void EntityProperties(EntityHandle entitySelected);
		void AssetProperties(AssetHandle assetSelected);
	};
}