#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "Entities/EntityManager.h"

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
		void SceneViewInput();
		void Properties(EntityHandle EntitySelected);
		void AssetTray();
		void SceneHierarchy(EntityHandle* entitySelected);
	};
}