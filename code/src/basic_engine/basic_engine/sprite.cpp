#include "sprite.h"
#include "game.h"

#include "sdl_asset/sdl_texture_asset.h"

namespace basic_engine {
	Sprite::Sprite(const SpriteParameter& params)
		: mFlip{ params.Flip } 
	{
		auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, params.TexturePath, params.TextureLabel);

		if (textHandle.has_value()) {
			mTexture = dynamic_cast<SdlTextureAsset*>(Game::AssetService().GetAsset(textHandle.value()));
			Move(params.X, params.Y);
		}
	}

	Sprite::Sprite(SdlTextureAsset* textureAsset, const Vector2f& pos, SDL_RendererFlip flip)
		: mTexture{ textureAsset }
		, mSourceRect{ 0, 0, textureAsset->Width(), textureAsset->Height() }
		, mFlip {flip } {
		Move(pos.x, pos.y);
	}

	Sprite::Sprite(SdlTextureAsset* textureAsset, const Rectangle<int32_t>& srcRectangle, SDL_RendererFlip flip)
		: mTexture{ textureAsset }
		, mSourceRect{srcRectangle.Left, srcRectangle.Top, srcRectangle.Width, srcRectangle.Height }
		, mFlip{ flip } {
		mDestinationRect = mSourceRect;
		mDestinationRect.x = 0;
		mDestinationRect.y = 0;
	}

	void Sprite::Update(double tickTimeInMsec) {
	}


	void Sprite::Move(float offsetX, float offsetY) {
		mTransform.Move(offsetX, offsetY);
		mDestinationRect = { static_cast<int32_t>(mTransform.Pos().x),
			static_cast<int32_t>(mTransform.Pos().y),
			static_cast<int32_t>(mSourceRect.w),
			static_cast<int32_t>(mSourceRect.h) };
	}

	const Transformation& Sprite::Transform() const {
		return mTransform;
	}

	void Sprite::Display(SDL_Renderer* renderer) const {
		if (nullptr != renderer && nullptr != mTexture) {
			// Sprite
			SDL_RenderCopyEx(renderer, mTexture->Texture(), &mSourceRect, &mDestinationRect, 0, nullptr, mFlip);
		}
	}
}