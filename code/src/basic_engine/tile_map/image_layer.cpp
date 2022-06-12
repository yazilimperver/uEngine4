#include "image_layer.h"

#include "SDL.h"
#include "SDL_image.h"

#include "tileson.hpp"

#include "basic_engine/game.h"

#include "sdl_asset/sdl_texture_asset.h"

namespace basic_engine {
	ImageLayer::ImageLayer(std::string_view rootPath, tson::Layer& layer)	{
		mParallaxFactorX = layer.getParallax().x;
		mParallaxFactorY = layer.getParallax().y;

		auto imagePath = std::string{ rootPath.data() } + layer.getImage();
		auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, imagePath, layer.getName());

		if (textHandle.has_value()) {
			auto winWidth = Game::WindowParameters().Width;
			auto winHeight = Game::WindowParameters().Height;

			auto loadedTexture = dynamic_cast<SdlTextureAsset*>(Game::AssetService().GetAsset(textHandle.value()));
			mSprite = std::make_unique<Sprite>(loadedTexture, 
				Vector2i{ static_cast<int32_t>(loadedTexture->Width() * 0.5F + layer.getOffset().x ),
						  static_cast<int32_t>(loadedTexture->Height() * 0.5F + layer.getOffset().y ) },
				SDL_FLIP_NONE);
		}
	}

	void ImageLayer::Update(double deltaTimeInMsec) {
		mSprite->Update(deltaTimeInMsec);
	}

	void ImageLayer::Display(SDL_Renderer* renderer) const {
		mSprite->Display(renderer, mParallaxFactorX, mParallaxFactorY);
	}
}