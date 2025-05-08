#pragma once
#include <glad/glad.h>
#include <string>
#include <memory>

#include "VertexArray.h"
#include "ShaderProgram.h"

namespace RenderToy
{
	class Framebuffer
	{
	private:
		uint32_t m_fbo, m_rbo;
		uint32_t m_FramebufferTexture;
		ShaderProgram m_Shaders;
		std::unique_ptr<VertexArray> m_OutputQuad = nullptr;

		float m_Width, m_Height;

	public:
		Framebuffer(float width, float height);

		void Bind();
		void Unbind();

		void Clear();
		void Render();

		void SetSize(float width, float height);
		uint32_t GetFramebufferTextureID();

		~Framebuffer();

	private:
		void InitialiseFrameBuffer();
		void InitialiseVAO();
	};
}