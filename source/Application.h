#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"

namespace RenderToy
{
	struct ApplicationState
	{
		bool showDemoWindow = true;
		bool showAnotherWindow = false;
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