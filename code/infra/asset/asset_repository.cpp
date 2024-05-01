#include "asset_repository.h"

#include "sdl_asset/sdl_texture_asset.h"
#include "sdl_asset/sdl_texture_loader.h"

#include "utility/unique_id_generator.h"

namespace infra {

	void infra::AssetRepository::RegisterLoader(std::shared_ptr<AssetLoader> loader) {
		if (!mAssetLoaders.contains(loader->Name()) ){
			// SDL'e ozel ayarlamalari yapalim
			if (basic_engine::SdlTextureAsset::SdlTextureTypeStr == loader->Name()) {
				reinterpret_cast<basic_engine::SdlTextureLoader*>(loader.get())->AssignRenderer(mRenderer);
			}

			mAssetLoaders[loader->Name()] = loader;
            loader->SetLoaderHandle(UniqueIDGenerator::GetNextID());

            mAssetLoadersByHandle[loader->Handle()] = loader;
		}
	}

    std::optional<AssetLoaderHandle> AssetRepository::LoaderHandle(std::string_view loaderName) {
        if (auto itr = mAssetLoaders.find(static_cast<std::string>(loaderName)); itr != mAssetLoaders.end()) {
            return itr->second->Handle();
        }
        else {
            return std::nullopt;
        }
    }

    std::optional<AssetHandle> AssetRepository::LoadAsset(AssetLoaderHandle handle, std::string_view path, std::string_view label) {
        // oncelikle yukleyici var mi?
        if (auto itr = mAssetLoadersByHandle.find(handle); itr != mAssetLoadersByHandle.end()) {
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
                    mAssetPool[assetHandle] = loadedAsset;

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

	std::optional<AssetHandle> infra::AssetRepository::LoadAsset(AssetLoaderName name, std::string_view path, std::string_view label) {
		// oncelikle yukleyici var mi?
		if (auto itr = mAssetLoaders.find(name); itr != mAssetLoaders.end()) {
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
					mAssetPool[assetHandle] = loadedAsset;

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

	void infra::AssetRepository::DisposeAsset(AssetHandle assetHandle) {
		if (auto itr = mAssetPool.find(assetHandle); itr != mAssetPool.end()) {
			auto assetInfo = itr->second->Info();
			mLoadedAssets.erase(assetInfo.mPath);			
            mAssetLoadersByHandle[assetInfo.mLoaderHandle]->Dispose(itr->second);
			mAssetPool.erase(assetHandle);
		}
	}

    std::shared_ptr<Asset> AssetRepository::SharedAsset(AssetHandle assetHandle) {
        if (auto itr = mAssetPool.find(assetHandle); itr != mAssetPool.end()) {
            return itr->second;
        }
        else {
            return nullptr;
        }
    }

	Asset* infra::AssetRepository::GetAsset(AssetHandle assetHandle) {
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
			if (basic_engine::SdlTextureAsset::SdlTextureTypeStr == loader.second->Name()) {
				reinterpret_cast<basic_engine::SdlTextureLoader*>(loader.second.get())->AssignRenderer(mRenderer);
			}
		}
	}
}