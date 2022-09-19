#include "image_layer.h"

#include "SDL.h"
#include "SDL_image.h"

#include "tileson.hpp"

#include "basic_engine/game.h"

#include "sdl_asset/sdl_texture_asset.h"

#include "spdlog/spdlog.h"

namespace basic_engine {
	ImageLayer::ImageLayer(std::string_view rootPath, tson::Layer& layer)	{
		mParallaxFactorX = layer.getParallax().x;
		mParallaxFactorY = layer.getParallax().y;
		mIsRepeatXEnabled = layer.hasRepeatX();
		mIsRepeatYEnabled = layer.hasRepeatY();

		auto imagePath = std::string{ rootPath.data() } + layer.getImage();
		auto textHandle = Game::GetAssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, imagePath, layer.getName());

		if (textHandle.has_value()) {
			auto winWidth = Game::WindowParameters().Width;
			auto winHeight = Game::WindowParameters().Height;

			auto loadedTexture = dynamic_cast<SdlTextureAsset*>(Game::GetAssetService().GetAsset(textHandle.value()));
			mSprite = std::make_unique<Sprite>(loadedTexture, 
				Vector2i{ static_cast<int32_t>(loadedTexture->Width() * 0.5F + layer.getOffset().x ),
						  static_cast<int32_t>(loadedTexture->Height() * 0.5F + layer.getOffset().y ) },
				SDL_FLIP_NONE);

			mImageWidth = loadedTexture->Width();

			if (mIsRepeatXEnabled) {
				mParallaxFactorX = 1.0;
				mParallaxFactorY = 1.0;
			}
		}
	}

	void ImageLayer::Update(double deltaTimeInMsec) {
		if (true == mIsRepeatXEnabled) {
			// artik resmi bir kaydiriyoruz
			if (Game::GameCamera().Target().x > mSprite->DestinationRect().x + mImageWidth) {
				auto pos = mSprite->Transform().Pos();
				mSprite->SetPosition(pos.x + mImageWidth, pos.y);

				spdlog::error("Image center moved!");
			}
			else if (Game::GameCamera().Target().x < mSprite->DestinationRect().x) {
				auto pos = mSprite->Transform().Pos();
				mSprite->SetPosition(pos.x - mImageWidth, pos.y);

				spdlog::error("Image center moved!");
			}
		}

		mSprite->Update(deltaTimeInMsec);
	}

	void ImageLayer::Display(SDL_Renderer* renderer) const {
		mSprite->Display(renderer, mParallaxFactorX, mParallaxFactorY);

		if (true == mIsRepeatXEnabled){
			{
				auto rect = mSprite->DestinationRect(mParallaxFactorX, mParallaxFactorY);
				rect.x += mImageWidth;

				mSprite->Display(renderer, rect, mParallaxFactorX, mParallaxFactorY);
			}
			{
				auto rect = mSprite->DestinationRect(mParallaxFactorX, mParallaxFactorY);
				rect.x -= mImageWidth;

				mSprite->Display(renderer, rect, mParallaxFactorX, mParallaxFactorY);
			}
		}
	}
}