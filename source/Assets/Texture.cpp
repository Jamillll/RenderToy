#include "Texture.h"
#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace RenderToy
{
	Texture::Texture(const std::string& path, bool flipped)
		: Path(path)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		stbi_set_flip_vertically_on_load(flipped);

		int width, height, nrchannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrchannels, 0);

		if (data)
		{
			GLenum format;

			switch (nrchannels)
			{
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				format = GL_RGB;
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
	}

	uint32_t Texture::GetID()
	{
		return m_ID;
	}

	void Texture::Activate(int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}