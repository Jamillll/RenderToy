#include "BufferLayout.h"
#include <iostream>

namespace RenderToy
{
	BufferElement::BufferElement(const std::string& name, ShaderDataType type, bool normalised) :
		Name(name), Type(type), Normalised(normalised), Offset(0), Size(ShaderDataTypeSize(type))
	{
	}

	BufferLayout::BufferLayout(std::initializer_list<BufferElement> layout)
		: m_Layout(layout)
	{
		for (size_t i = 0; i < m_Layout.size(); i++)
		{
			m_Layout[i].Offset = m_Stride;

			m_Stride += (m_Layout[i].Size * OpenGLTypeSize(ShaderDataTypeToGLenum(m_Layout[i].Type)));
		}
	}

	BufferLayout::~BufferLayout()
	{
	}

	uint32_t BufferLayout::GetStride()
	{
		return m_Stride;
	}

	const std::vector<BufferElement>& BufferLayout::GetLayout()
	{
		return m_Layout;
	}

	GLenum ShaderDataTypeToGLenum(ShaderDataType type)
	{
		switch (type)
		{
		case RenderToy::Float: return GL_FLOAT;
		case RenderToy::Float2: return GL_FLOAT;
		case RenderToy::Float3: return GL_FLOAT;
		case RenderToy::Float4: return GL_FLOAT;
		case RenderToy::Mat4: return GL_FLOAT;
		case RenderToy::Bool: return GL_BOOL;
		default:
			std::cout << "No conversion from ShaderDataType to GLenum" << std::endl;
			return NULL;
		}
	}

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case RenderToy::Float: return 1;
		case RenderToy::Float2: return 2;
		case RenderToy::Float3: return 3;
		case RenderToy::Float4: return 4;
		case RenderToy::Mat4: return 16;
		case RenderToy::Bool: return 1;
		default:
			std::cout << "No Size value for this ShaderDataType" << std::endl;
			return NULL;
		}
	}
	uint32_t OpenGLTypeSize(GLenum type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(float);
		case GL_BOOL: return sizeof(bool);
		default:
			std::cout << "No size conversion for this OpenGL type" << std::endl;
			return NULL;
		}
	}
}