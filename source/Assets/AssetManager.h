#pragma once
#include <vector>
#include <memory>
#include <string>

namespace RenderToy
{
	typedef unsigned int AssetHandle;

	enum AssetType
	{
		NULLASSET = 0,
		MODEL = 1,
	};

	class Asset
	{
	public:
		AssetHandle assetHandle = -1;
		AssetType assetType = AssetType::NULLASSET;
		std::string path;
		std::string name;
	};
	
	class AssetManager
	{
	private:
		static std::vector<std::unique_ptr<Asset>> m_Assets;

	public:
		static void Initialise();

		static void CreateModel(const std::string& path);

		static size_t Size();
		static Asset* GetAssetByHandle(AssetHandle handle);
		static AssetHandle GetAssetByPath(const std::string& path);
	};

}