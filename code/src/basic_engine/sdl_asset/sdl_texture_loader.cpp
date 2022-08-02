#include "sdl_asset/sdl_texture_loader.h"

#include "spdlog/spdlog.h"

#include "SDL.h"
#include "SDL_image.h"

#include "sdl_texture_asset.h"

#include "utility/unique_id_generator.h"

namespace basic_engine {
    std::unique_ptr<Asset> SdlTextureLoader::Load(std::string_view path, std::string_view label) {
        auto newAsset = std::make_unique<SdlTextureAsset>();

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
        newAsset->InfoRef().mStatus = AssetStatus::LoadSuccessful;
        newAsset->InfoRef().mPath = path.data();
        newAsset->InfoRef().mLabel = label.data();

        // SDL_Surface'tan kurtulalim
        SDL_FreeSurface(surface);

		return std::move(newAsset);
	}

    void SdlTextureLoader::AssignRenderer(SDL_Renderer* renderer) {
        mRenderer = renderer;
    }

    void SdlTextureLoader::Dispose(std::unique_ptr<Asset>& asset) {
        SdlTextureAsset* sdlTextureAsset = dynamic_cast<SdlTextureAsset*>(asset.get());
        SDL_DestroyTexture(sdlTextureAsset->Texture());
        sdlTextureAsset->InfoRef().mStatus = AssetStatus::NotActive;
	}

	AssetType SdlTextureLoader::Type()	{
		return SdlTextureAsset::SdlTextureTypeStr;
	}
}