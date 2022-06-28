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
			mWidth = mTexture->Width();
			mHeight = mTexture->Height();
			mSourceRect = SDL_Rect{ 0, 0, mWidth, mHeight };
			mDestinationRect = mSourceRect;
			SetPosition(params.X, params.Y);
		}
	}

	Sprite::Sprite(SdlTextureAsset* textureAsset, const Vector2i& pos, SDL_RendererFlip flip)
		: mTexture{ textureAsset }
		, mFlip {flip } {

		if (nullptr != mTexture) {
			mWidth = mTexture->Width();
			mHeight = mTexture->Height();
			mSourceRect = SDL_Rect{ 0, 0, mWidth, mHeight };
			mDestinationRect = mSourceRect;
			SetPosition(pos.x, pos.y);
		}
	}

	Sprite::Sprite(SdlTextureAsset* textureAsset, const Rectangle<int32_t>& srcRectangle, SDL_RendererFlip flip)
		: mTexture{ textureAsset }
		, mSourceRect{srcRectangle.Left, srcRectangle.Top, srcRectangle.Width, srcRectangle.Height }
		, mFlip{ flip } {
		mDestinationRect = mSourceRect;
		mWidth = srcRectangle.Width;
		mHeight = srcRectangle.Height;
		/// CHECK
	}

	Sprite::Sprite(const Sprite* spriteInstance) {
		mTransform = spriteInstance->mTransform;
		mDestinationRect = spriteInstance->mDestinationRect;
		mSourceRect = spriteInstance->mSourceRect;
		mTexture = spriteInstance->mTexture;
		mHeight = spriteInstance->mHeight;
		mWidth = spriteInstance->mWidth;
		mFlip = spriteInstance->mFlip;
	}

	void Sprite::Update(double tickTimeInMsec) {
	}

	void Sprite::SetPosition(int32_t offsetX, int32_t offsetY) {
		mTransform.SetPosition(offsetX, offsetY);

		mDestinationRect.x = mTransform.Pos().x - static_cast<int>(mWidth * 0.5F);
		mDestinationRect.y = mTransform.Pos().y - static_cast<int>(mHeight * 0.5F);;
	}

	void Sprite::Rotate(float rotate) {
		mTransform.Rotate(rotate);
	}

	void Sprite::SetScale(const Vector2f& scale) {
		mTransform.SetScale(scale);

		mDestinationRect.x = static_cast<int>(mTransform.Pos().x - mWidth * scale.x * 0.5f);
		mDestinationRect.y = static_cast<int>(mTransform.Pos().y - mHeight * scale.y * 0.5f);

		mDestinationRect.w = static_cast<int>(scale.x * mWidth);
		mDestinationRect.h = static_cast<int>(scale.y * mHeight);
	}

	SDL_Rect Sprite::DestinationRect(float cameraSpeedRatioX, float cameraSpeedRatioY) const
	{
		SDL_Rect displayRect = mDestinationRect;
		displayRect.x -= static_cast<int32_t>(Game::GameCamera().Center().x * cameraSpeedRatioX);
		displayRect.y -= static_cast<int32_t>(Game::GameCamera().Center().y * cameraSpeedRatioY);

		return displayRect;
	}

	const Transformation& Sprite::Transform() const {
		return mTransform;
	}

	basic_engine::Sprite* Sprite::Clone() {
		return new Sprite(this);
	}

	void Sprite::Display(SDL_Renderer* renderer, float cameraSpeedRatioX, float cameraSpeedRatioY) const {
		if (nullptr != renderer && nullptr != mTexture) {		
			SDL_Rect displayRect = DestinationRect(cameraSpeedRatioX, cameraSpeedRatioY);
			SDL_RenderCopyEx(renderer, mTexture->Texture(), &mSourceRect, &displayRect, mTransform.Rotation(), nullptr, mFlip);
		}
	}
	void Sprite::Display(SDL_Renderer* renderer, const SDL_Rect& destRect, float cameraSpeedRatioX, float cameraSpeedRatioY) const	{
		if (nullptr != renderer && nullptr != mTexture) {
			SDL_RenderCopyEx(renderer, mTexture->Texture(), &mSourceRect, &destRect, mTransform.Rotation(), nullptr, mFlip);
		}
	}
}