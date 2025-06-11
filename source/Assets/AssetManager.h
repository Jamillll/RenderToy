#pragma once
#include <vector>
#include <memory>
#include <string>

namespace RenderToy
{
	enum AssetType
	{
		NULLASSET = 0,
		TEXTURE = 1,
		MODEL = 2,
	};

	class Asset
	{
	public:
		unsigned int AssetHandle = 0;
		AssetType AssetType = AssetType::NULLASSET;
	};
	
	class AssetManager
	{
	private:
		std::vector<std::unique_ptr<Asset>> m_Assets;

	public:
		AssetManager();

		void CreateTexture(const std::string& path, bool flipped = false);
		void CreateModel(const std::string& path, bool flipped = false);
	};

}