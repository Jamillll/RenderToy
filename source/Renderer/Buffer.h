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
	public:
		Buffer(uint32_t type);
		~Buffer();

		void UploadBufferData(int size, void* data, GLenum usage);
		void Bind();

		uint32_t GetID();
	};
}