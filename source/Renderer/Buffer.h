#pragma once
#include <glad/glad.h>
#include <string>

namespace RenderToy
{
	class Buffer
	{
	private:
		uint32_t m_ID = NULL;
		uint32_t m_Type = NULL;
		uint32_t m_Count = 0;
	public:
		Buffer(uint32_t type);
		~Buffer();

		void UploadBufferData(int size, void* data, uint32_t count, GLenum usage = GL_STATIC_DRAW);
		void Bind();

		uint32_t GetID();
		uint32_t GetCount();
	};
}