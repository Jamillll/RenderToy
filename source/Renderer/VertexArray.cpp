#include "VertexArray.h"

namespace RenderToy
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		m_vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::AddIndexBuffer()
	{
		m_ebo = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER);
	}

	void VertexArray::UploadVertexData(int size, void* data, uint32_t count, GLenum usage)
	{
		m_vbo->UploadBufferData(size, data, count, usage);
	}

	void VertexArray::UploadIndexData(int size, void* data, uint32_t count, GLenum usage)
	{
		m_ebo->UploadBufferData(size, data, count, usage);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_VertexArrayID);
		m_vbo->Bind();

		if (m_ebo != nullptr) m_ebo->Bind();
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::Draw()
	{
		Bind();

		if (m_ebo == nullptr)
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vbo->GetCount());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, m_ebo->GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
}
