#include "sprite.h"
#include "game.h"

#include "sdl_asset/sdl_texture_asset.h"

namespace basic_engine {
	Sprite::Sprite(const SpriteParameter& params)
		: mFlip{ params.Flip } 
	{
		mBoundary = { static_cast<int32_t>(params.X - params.Width), 
					  static_cast<int32_t>(params.Y - params.Height), 
					  static_cast<int32_t>(params.Width), 
			          static_cast<int32_t>(params.Height)};

		mTransform.Move(params.X, params.Y);
		mBoundary.x = static_cast<int32_t>(mTransform.Pos().x);
		mBoundary.y = static_cast<int32_t>(mTransform.Pos().y);

		auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, params.TexturePath, params.TextureLabel);

		if (textHandle.has_value()) {
			mTexture = dynamic_cast<SdlTextureAsset*>(Game::AssetService().GetAsset(textHandle.value()));
		}
	}

	void Sprite::Update(double tickTimeInMsec) {
		mBoundary.x = static_cast<int32_t>(mTransform.Pos().x);
		mBoundary.y = static_cast<int32_t>(mTransform.Pos().y);
	}

	Transformation& Sprite::Transform() {
		return mTransform;
	}

	void Sprite::Display(SDL_Renderer* renderer) const {
		if (nullptr != renderer && nullptr != mTexture) {

			// Boundary
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x80);
			SDL_RenderFillRect(renderer, &mBoundary);

			// Sprite
			SDL_RenderCopyEx(renderer, mTexture->Texture(), nullptr, &mBoundary, 0, nullptr, mFlip);
		}
	}
}