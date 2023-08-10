#include "gtest/gtest.h"

#include "asset/asset_repository.h"

#include "sdl_asset/sdl_texture_asset.h"
#include "sdl_asset/sdl_texture_loader.h"

#include "SDL.h"
#include "SDL_image.h"

using namespace basic_engine;

TEST(SdlTextureAsset, AssetInfoDefaultParams) {
	SdlTextureAsset instance;

	ASSERT_EQ(instance.Texture(), nullptr);
	ASSERT_EQ(instance.Info().mHandle, 0);
	ASSERT_EQ(instance.Info().mStatus, infra::AssetInfo::Status::NotActive);
	ASSERT_STREQ(instance.Info().mLabel.c_str(), "");
	ASSERT_STREQ(instance.Info().mPath.c_str(), "");
}

TEST(SdlTextureAssetLoader, AssetInfoDefaultParams) {
	std::unique_ptr<SdlTextureLoader> sdlTextureLoader = std::make_unique<SdlTextureLoader>();

    SDL_Window* window;
    SDL_Renderer* renderer;
    constexpr uint32_t ScreenWidth  = 640;
    constexpr uint32_t ScreenHeight = 480;

    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    }

    window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, 0);
    if (window == nullptr) {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
    }

	infra::AssetRepository assetRepository;
	assetRepository.RegisterLoader(std::move(sdlTextureLoader));

    auto textureHandle = assetRepository.LoadAsset(SdlTextureAsset::SdlTextureTypeStr, "tree.png", "testImage");  
}