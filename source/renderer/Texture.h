#pragma once
#include <string>
#include <glad/glad.h>

namespace RenderToy
{
	class Texture
	{
	private:
		uint32_t m_id;

	public:
		Texture(const std::string& name, bool flipped = false, int32_t dataFormat = GL_RGB);
		~Texture();

		uint32_t GetID();
		void Activate(int textureUnit);
		void Bind();
		void Unbind();
	};
}