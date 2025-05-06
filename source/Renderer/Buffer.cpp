#include "Buffer.h"
#include "iostream"

namespace RenderToy
{
	Buffer::Buffer(uint32_t type)
		:m_Type(type)
	{
		glGenBuffers(1, &m_ID);
		Bind();
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_ID);
		glBindBuffer(m_Type, 0);
	}

	void Buffer::UploadBufferData(int size, void* data, GLenum usage)
	{
		Bind();
		glBufferData(m_Type, size, data, usage);
	}

	void Buffer::Bind()
	{
		glBindBuffer(m_Type, m_ID);
	}

	uint32_t Buffer::GetID()
	{
		return m_ID;
	}
}