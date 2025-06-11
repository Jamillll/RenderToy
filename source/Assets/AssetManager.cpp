#include "AssetManager.h"
#include "Texture.h"

namespace RenderToy
{
	AssetManager::AssetManager()
	{
		// Creating a null asset which can be returned in the event of errors
		std::unique_ptr<Asset> nullAsset = std::make_unique<Asset>();
		nullAsset->AssetType = AssetType::NULLASSET;
		nullAsset->AssetHandle = 0;

		m_Assets.push_back(std::move(nullAsset));
	}

	void AssetManager::CreateTexture(const std::string& path, bool flipped)
	{
		std::unique_ptr<Texture> texture = std::make_unique<Texture>(path, flipped);
		texture->AssetHandle = m_Assets.size();
		texture->AssetType = AssetType::TEXTURE;

		m_Assets.push_back(std::move(texture));
	}
}