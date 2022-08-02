#include "asset_repository.h"

#include "sdl_asset/sdl_texture_asset.h"
#include "sdl_asset/sdl_texture_loader.h"

namespace basic_engine {

	void basic_engine::AssetRepository::RegisterLoader(std::unique_ptr<AssetLoader> loader) {
		if (!mAssetLoaders.contains(loader->Type()) ){

			if (SdlTextureAsset::SdlTextureTypeStr == loader->Type()) {
				reinterpret_cast<basic_engine::SdlTextureLoader*>(loader.get())->AssignRenderer(mRenderer);
			}

			mAssetLoaders[loader->Type()] = std::move(loader);
		}
	}

	std::optional<AssetHandle> basic_engine::AssetRepository::LoadAsset(AssetType type, std::string_view path, std::string_view label) {
		// oncelikle yukleyici var mi?
		if (auto itr = mAssetLoaders.find(type); itr != mAssetLoaders.end()) {
			// var ise zaten yuklenmis mi?
			std::string pathStr{ path.data() };
			if (auto pathItr = mLoadedAssets.find(pathStr); pathItr == mLoadedAssets.end()) {
				// yuklenmemis ise ekleyelim 
				auto loadedAsset = itr->second->Load(path, label);

				// yukleme ok mi?
				if (loadedAsset) {
					auto assetHandle = loadedAsset->Info().mHandle;
					
					// once yuklenen listesine ekleyelim
					mLoadedAssets[pathStr] = assetHandle;

					// Etikete gore anahtarlanan listeye ekleyelim
					mLabeledAssets[std::string(label.data())] = assetHandle;

					// sonrada havuza tasiyalim
					mAssetPool[assetHandle] = std::move(loadedAsset);

					return assetHandle;
				}
				else {
					return std::nullopt;
				}
			}
			else {
				// yuklenmis olanin essiz numarasini donelim
				return mAssetPool[pathItr->second]->Info().mHandle;
			}
		}
		else {
			return std::nullopt;
		}
	}

	void basic_engine::AssetRepository::DisposeAsset(AssetHandle assetHandle) {
		if (auto itr = mAssetPool.find(assetHandle); itr != mAssetPool.end()) {
			auto assetInfo = itr->second->Info();
			mLoadedAssets.erase(assetInfo.mPath);			
			mAssetLoaders[assetInfo.mType]->Dispose(itr->second);
			mAssetPool.erase(assetHandle);
		}
	}

	Asset* basic_engine::AssetRepository::GetAsset(AssetHandle assetHandle) {
		if (auto itr = mAssetPool.find(assetHandle); itr != mAssetPool.end()) {
			return itr->second.get();
		}
		else {
			return nullptr;
		}
	}
	Asset* AssetRepository::GetAsset(std::string_view label) {
		if (auto itr = mLabeledAssets.find(std::string(label.data())); itr != mLabeledAssets.end()) {
			return mAssetPool[itr->second].get();
		}
		else {
			return nullptr;
		}
	}
	void AssetRepository::AssignRenderer(SDL_Renderer* renderer) {
		mRenderer = renderer;

		for (auto& loader : mAssetLoaders) {
			if (SdlTextureAsset::SdlTextureTypeStr == loader.second->Type()) {
				reinterpret_cast<basic_engine::SdlTextureLoader*>(loader.second.get())->AssignRenderer(mRenderer);
			}
		}
	}
}