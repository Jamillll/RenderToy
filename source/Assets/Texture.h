#pragma once
#include <string>
#include "AssetManager.h"

namespace RenderToy
{
	class Texture
	{
	private:
		uint32_t m_ID;

	public:
		std::string Type;
		std::string Path;

		Texture(const std::string& path, bool flipped = false);
		~Texture();

		uint32_t GetID();
		void Activate(int textureUnit);
		void Bind();
		void Unbind();
	};
}