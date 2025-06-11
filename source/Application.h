#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace RenderToy
{
	struct ApplicationState
	{
		bool showDemoWindow = false;
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
	};
}