/**
 * @file asset_repository.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <unordered_map>

#include "asset_service.h"

namespace basic_engine {
	class AssetRepository 
		: public AssetService {
	public:
		virtual void RegisterLoader(std::unique_ptr<AssetLoader>) override;
		virtual std::optional<AssetHandle> LoadAsset(AssetType, std::string_view path, std::string_view label) override;
		virtual void DisposeAsset(AssetHandle) override;
		virtual Asset* GetAsset(AssetHandle) override;
		virtual Asset* GetAsset(std::string_view label) override;
		void AssignRenderer(SDL_Renderer* renderer);
	protected:
		SDL_Renderer* mRenderer{nullptr};
		std::unordered_map<AssetHandle, std::unique_ptr<Asset>> mAssetPool;
		std::unordered_map<std::string, AssetHandle> mLoadedAssets;
		std::unordered_map<std::string, AssetHandle> mLabeledAssets;
		std::unordered_map<AssetType, std::unique_ptr<AssetLoader>> mAssetLoaders;
	};
}
