#pragma once
#include <memory>

#include "ShaderProgram.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include "Framebuffer.h"
#include "Camera.h"

#include "../Assets/AssetManager.h"
#include "../Entities/EntityManager.h"

namespace RenderToy
{
	class Renderer
	{
	private:
		static std::unique_ptr<Framebuffer> m_Framebuffer;
		static std::unique_ptr<Camera> m_Camera;

		static ShaderProgram* temp_ModelShader;

	public:
		static void Initialise(float windowWidth, float windowHeight);

		static void Submit(EntityHandle entityHandle);
		static void Submit(VertexArray& vao, ShaderProgram shaders, TransformData transform);
		
		static Camera* GetCamera();
		static uint32_t GetFramebufferTextureID();

		static void StartFrame();
		static void EndFrame();
	};
}