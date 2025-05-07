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

	public:
		Framebuffer();

		void Bind();
		void Unbind();

		void Clear();
		void Render();

		uint32_t GetFramebufferTextureID();

		~Framebuffer();

	private:
		void InitialiseVAO();
	};
}