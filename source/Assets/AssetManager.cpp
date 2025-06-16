#include "AssetManager.h"
#include "Texture.h"
#include "Model.h"

#include <algorithm>

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
		model->path = path;

		m_Assets.push_back(std::move(model));
	}

	Asset* AssetManager::GetAssetByHandle(AssetHandle handle)
	{
		return m_Assets[handle].get();
	}

	AssetHandle AssetManager::GetAssetByPath(const std::string& path)
	{
		for (size_t i = 0; i < m_Assets.size(); i++)
		{
			std::string assetPath = m_Assets[i]->path;
			assetPath.erase(std::remove(assetPath.begin(), assetPath.end(), '/'), assetPath.end());
			assetPath.erase(std::remove(assetPath.begin(), assetPath.end(), '\\'), assetPath.end());

			std::string newPath = path;
			newPath.erase(std::remove(newPath.begin(), newPath.end(), '/'), newPath.end());
			newPath.erase(std::remove(newPath.begin(), newPath.end(), '\\'), newPath.end());

			if (assetPath == newPath)
			{
				return m_Assets[i]->assetHandle;
			}
		}

		return m_Assets[0]->assetHandle;
	}
}