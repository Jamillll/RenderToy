#include "Framebuffer.h"
#include "assert.h"

namespace RenderToy
{
	Framebuffer::Framebuffer(float width, float height) :
		m_Width(width), m_Height(height)
	{
		InitialiseFrameBuffer();
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Clear()
	{
		Bind();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::Render()
	{
		m_Shaders.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_FramebufferTexture);
		m_Shaders.setI1Uniform("u_FramebufferTexture", 0);

		m_OutputQuad->Draw();
	}


	void Framebuffer::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;

		glDeleteTextures(1, &m_FramebufferTexture);
		glDeleteRenderbuffers(1, &m_rbo);
		glDeleteFramebuffers(1, &m_fbo);
		InitialiseFrameBuffer();
	}

	uint32_t Framebuffer::GetFramebufferTextureID()
	{
		return m_FramebufferTexture;
	}

	Framebuffer::~Framebuffer()
	{
	}

	void Framebuffer::InitialiseFrameBuffer()
	{
		// Framebuffer Shaders 
		m_Shaders.CreateShaders(RESOURCES_PATH "shaders/fbVertex.shader", RESOURCES_PATH "shaders/fbFragment.shader");

		// VAO for the screen quad
		InitialiseVAO();

		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_FramebufferTexture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_FramebufferTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_FramebufferTexture, 0);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FrameBuffer incomplete");
	}

	void Framebuffer::InitialiseVAO()
	{
		float screenQuad[] = {
			 1.0f,  1.0f, 0.0f,  1.0f, 1.0f, // top right
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // bottom right
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // bottom left
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f  // top left 
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		BufferLayout layout = {
			{"Position", ShaderDataType::Float3},
			{"TexCoords", ShaderDataType::Float2}
		};

		m_OutputQuad = std::make_unique<VertexArray>(layout);
		m_OutputQuad->AddIndexBuffer();

		m_OutputQuad->UploadVertexData(sizeof(screenQuad), screenQuad, 4, GL_DYNAMIC_DRAW);
		m_OutputQuad->UploadIndexData(sizeof(indices), indices, 6, GL_DYNAMIC_DRAW);
	}
}