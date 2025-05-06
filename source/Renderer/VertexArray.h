#pragma once
#include <glad/glad.h>
#include <string>
#include <memory>

#include "Buffer.h"
#include "BufferLayout.h"

namespace RenderToy
{
	class VertexArray
	{
	private:
		uint32_t m_VertexArrayID;
		std::unique_ptr<Buffer> m_vbo = nullptr;
		std::unique_ptr<Buffer> m_ebo = nullptr;
	public:
		VertexArray(BufferLayout layout);
		~VertexArray();

		void AddIndexBuffer();

		void UploadVertexData(int size, void* data, uint32_t count, GLenum usage = GL_STATIC_DRAW);
		void UploadIndexData(int size, void* data, uint32_t count, GLenum usage = GL_STATIC_DRAW);

		void Bind();
		void Unbind();

		void Draw();
	};
}