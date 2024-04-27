#include "gis_map_loader.h"

#include "spdlog/spdlog.h"

#include "SDL.h"
#include "SDL_image.h"

#include "gis_map_asset.h"

#include "utility/unique_id_generator.h"

namespace gis_asset {
    std::shared_ptr<infra::Asset> GisMapLoader::Load(std::string_view path, std::string_view label) {
        if (nullptr == mRenderer){
            spdlog::error("SDL renderer is not assigned!");
            
            return nullptr;
        }

        SDL_Surface* surface = IMG_Load(path.data());        
        if (surface == nullptr) {
            spdlog::error("Failed to load texture: {}, {}!", path, SDL_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        if (texture == nullptr) {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
            return nullptr;
        }

        int32_t width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

        auto newAsset = std::make_shared<GisMapAsset>(texture, width, height);

        newAsset->InfoRef().mHandle = UniqueIDGenerator::GetNextID();
        newAsset->InfoRef().mStatus = infra::AssetStatus::LoadSuccessful;
        newAsset->InfoRef().mPath = path.data();
        newAsset->InfoRef().mLabel = label.data();
        newAsset->InfoRef().mLoaderHandle = mAssetLoaderHandle;

        // SDL_Surface'tan kurtulalim
        SDL_FreeSurface(surface);

		return newAsset;
	}

    void GisMapLoader::AssignRenderer(SDL_Renderer* renderer) {
        mRenderer = renderer;
    }

    void GisMapLoader::Dispose(std::shared_ptr<infra::Asset> asset) {
        GisMapAsset* gisAsset = dynamic_cast<GisMapAsset*>(asset.get());
        if (nullptr != gisAsset) {
            SDL_DestroyTexture(gisAsset->Texture());
            gisAsset->InfoRef().mStatus = infra::AssetStatus::NotActive;
        }
	}

	infra::AssetLoaderName GisMapLoader::Name()	{
		return GisMapAsset::GisMapAssetTypeStr;
	}
}