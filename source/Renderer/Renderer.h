#pragma once
#include <memory>

#include "ShaderProgram.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Framebuffer.h"
#include "Camera.h"

namespace RenderToy
{
	class Renderer
	{
	private:
		static std::unique_ptr<Framebuffer> m_Framebuffer;
		static std::unique_ptr<Camera> m_Camera;

	public:
		static void Initialise(float windowWidth, float windowHeight);

		static void Submit(VertexArray& vao, ShaderProgram shaders, glm::vec3 position, float rotation = 0, glm::vec3 pointOfRotation = { 0, 0, 0 });
		
		static Camera* GetCamera();
		static uint32_t GetFramebufferTextureID();

		static void StartFrame();
		static void EndFrame();
	};
}