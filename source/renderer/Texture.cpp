#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace RenderToy
{
	Texture::Texture(const std::string& name, bool flipped, int32_t dataFormat)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		stbi_set_flip_vertically_on_load(flipped);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else std::cout << name << " Texture failed to load" << std::endl;

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &m_id);
	}

	uint32_t Texture::GetID()
	{
		return m_id;
	}

	void Texture::Activate(int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
