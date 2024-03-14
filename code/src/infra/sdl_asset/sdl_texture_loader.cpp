#include "sdl_asset/sdl_texture_loader.h"

#include "spdlog/spdlog.h"

#include "SDL.h"
#include "SDL_image.h"

#include "sdl_texture_asset.h"

#include "utility/unique_id_generator.h"

namespace basic_engine {
    std::shared_ptr<infra::Asset> SdlTextureLoader::Load(std::string_view path, std::string_view label) {
        auto newAsset = std::make_shared<SdlTextureAsset>();

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

        newAsset->AssignTexture(texture);

        newAsset->InfoRef().mHandle = UniqueIDGenerator::GetNextID();
        newAsset->InfoRef().mStatus = infra::AssetStatus::LoadSuccessful;
        newAsset->InfoRef().mPath = static_cast<std::string>(path);
        newAsset->InfoRef().mLabel = static_cast<std::string>(label);
        newAsset->InfoRef().mLoaderHandle = mAssetLoaderHandle;

        // SDL_Surface'tan kurtulalim
        SDL_FreeSurface(surface);

		return newAsset;
	}

    void SdlTextureLoader::AssignRenderer(SDL_Renderer* renderer) {
        mRenderer = renderer;
    }

    void SdlTextureLoader::Dispose(std::shared_ptr<infra::Asset> asset) {
        SdlTextureAsset* sdlTextureAsset = dynamic_cast<SdlTextureAsset*>(asset.get());
        if (nullptr != sdlTextureAsset) {
            SDL_DestroyTexture(sdlTextureAsset->Texture());
            sdlTextureAsset->InfoRef().mStatus = infra::AssetStatus::NotActive;
        }
	}

    infra::AssetLoaderName SdlTextureLoader::Name()	{
		return SdlTextureAsset::SdlTextureTypeStr;
	}
}