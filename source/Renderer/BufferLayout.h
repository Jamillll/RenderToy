#pragma once
#include <string>
#include <vector>
#include <glad\glad.h>

namespace RenderToy
{
	enum ShaderDataType
	{
		Float = 0,
		Float2 = 1,
		Float3 = 2,
		Float4 = 3,
		Mat4 = 4,
		Bool = 5,
	};

	GLenum ShaderDataTypeToGLenum(ShaderDataType type);
	uint32_t ShaderDataTypeSize(ShaderDataType type);
	uint32_t OpenGLTypeSize(GLenum type);

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalised = false;

		BufferElement(const std::string& name, ShaderDataType type, bool normalised = false);
	};

	class BufferLayout
	{
	private:
		uint32_t m_Stride = 0;
		std::vector<BufferElement> m_Layout;

	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> layout);
		~BufferLayout();

		uint32_t GetStride();
		const std::vector<BufferElement>& GetLayout();
	};
}