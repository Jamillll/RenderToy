#include "AssetManager.h"
#include "Texture.h"
#include "Model.h"

namespace RenderToy
{
	std::vector<std::unique_ptr<Asset>> AssetManager::m_Assets;

	void AssetManager::Initialise()
	{
		// Creating a null asset which can be returned in the event of errors
		std::unique_ptr<Asset> nullAsset = std::make_unique<Asset>();
		nullAsset->assetType = AssetType::NULLASSET;
		nullAsset->assetHandle = 0;

		m_Assets.push_back(std::move(nullAsset));
	}

	void AssetManager::CreateModel(const std::string& path)
	{
		std::unique_ptr<Model> model = std::make_unique<Model>(path);
		model->assetHandle = m_Assets.size();
		model->assetType = AssetType::MODEL;

		m_Assets.push_back(std::move(model));
	}

	Asset* AssetManager::GetAssetByHandle(AssetHandle handle)
	{
		return m_Assets[handle].get();
	}
}