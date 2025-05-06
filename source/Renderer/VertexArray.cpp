#include "VertexArray.h"

namespace RenderToy
{
	VertexArray::VertexArray(BufferLayout layout)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		m_vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER);

		std::vector<BufferElement> elements(layout.GetLayout());

		for (size_t i = 0; i < elements.size(); i++)
		{
			glVertexAttribPointer(
				i, 
				ShaderDataTypeSize(elements[i].Type),
				ShaderDataTypeToGLenum(elements[i].Type),
				elements[i].Normalised,
				layout.GetStride(),
				(void*)elements[i].Offset);
			glEnableVertexAttribArray(i);
		}

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
