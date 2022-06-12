#include "sprite_sheet.h"
#include "sdl_asset/sdl_texture_asset.h"

#include "sprite_sheet/sprite_sheet_serializer.h"
#include "utility/json_data_parser.h"

#include "spdlog/spdlog.h"

#include "basic_engine/game.h"


namespace basic_engine {
    SpriteSheet::SpriteSheet(std::string_view spriteSheetConfig, const Rectangle<int32_t>& spriteBoundary, bool paused, bool looped)
        : mCurrentAnimation{ nullptr }
        , mSpriteSheetConfig{ spriteSheetConfig }
        , mDestinationRect {spriteBoundary.Left, spriteBoundary.Top, spriteBoundary.Width, spriteBoundary.Height }
        , mCurrentFrameIndex{ 0 }
        , mIsPaused{ paused }
        , mIsLooped{ looped }
        , mCurrentTexture{ nullptr } {

		mWidth = spriteBoundary.Width;
		mHeight = spriteBoundary.Height;
    }

	void SpriteSheet::EnableHorizontalFlipped()
	{
		mIsHorizontalFlipped = true; mIsVerticalFlipped = false; mRenderFlip = SDL_FLIP_HORIZONTAL;
	}

	bool SpriteSheet::IsVerticalFlipped() const
	{
		return mIsVerticalFlipped;
	}

	void SpriteSheet::EnableVerticalFlipped() {
		mIsVerticalFlipped = true; mIsHorizontalFlipped = false;  mRenderFlip = SDL_FLIP_VERTICAL;
	}

	void SpriteSheet::DisableFlip() { 
        mIsVerticalFlipped = false; mIsHorizontalFlipped = false;  mRenderFlip = SDL_FLIP_NONE; 
    }

    std::optional<SpriteSheetParameters> SpriteSheet::ParseConfigFile(const std::string& config) {
        // Json dosyasini okuyalim
        if (!mSpriteSheetConfig.empty()) {
            JsonDataParser<basic_engine::SpriteSheetParameters> jsonParser;
            return jsonParser.Deserialize(mSpriteSheetConfig);
        }
        else {
            spdlog::error("No spritesheet config file is provided!");
            return std::nullopt;
        }
    }

    bool SpriteSheet::Initialize() {
        bool isInitialized{ false };
        if (auto parameters = ParseConfigFile(mSpriteSheetConfig); parameters.has_value()) {
            mLastUsedParameters = parameters.value();

            mFrameTime = TimeInMSec{ mLastUsedParameters.FrameTime };

            // oncelikle ana doku dosyalarini okuyalim
            for (auto& texturePair : mLastUsedParameters.TextureFiles) {
                auto textureLabel = texturePair.first;
                auto texturePath = texturePair.second;
                auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, texturePath, textureLabel);

                if (textHandle.has_value()) {
                    mTextureList[textureLabel] = dynamic_cast<SdlTextureAsset*>(Game::AssetService().GetAsset(textHandle.value()));
                }
                else {
                    mTextureList[textureLabel] = nullptr;
                }
            }

            // Simdi animasyonlari okuyalim
            for (const auto& animation : mLastUsedParameters.Animations) {
                if (mTextureList.contains(animation.TextureName)) {
                    mLoadedAnimations[animation.AnimationName]
                        = std::make_unique<Animation>(animation.AnimationName, 
                            animation.AnimationFrames, 
                            mTextureList[animation.TextureName]);
                }
                else {
                    mLoadedAnimations[animation.AnimationName] = nullptr;
                    spdlog::error("Animation texture: {} not found!", animation.TextureName);
                }
            }

            if (mLoadedAnimations.contains(mLastUsedParameters.InitialAnimation)) {
                SetAnimation(mLastUsedParameters.InitialAnimation);
                isInitialized = true;
            }
            else {
                spdlog::error("Initial animation: {} not found!", mLastUsedParameters.InitialAnimation);
            }

        }
        else {
            spdlog::error("Spritesheet parse error, so spritesheet not updated!");
        }

        return isInitialized;
    }

    void SpriteSheet::SetAnimation(std::string_view animationLabel) {
        if (mCurrentAnimationLabel != animationLabel) {
            auto itr = mLoadedAnimations.find(std::string(animationLabel.data()));

            if (itr != mLoadedAnimations.end()) {
                mCurrentAnimationLabel = animationLabel;

                mCurrentAnimation = itr->second.get();
                mCurrentTexture = mCurrentAnimation->SpriteSheet();
                mCurrentFrameIndex = 0;

                SetFrame(mCurrentFrameIndex);
            }
        }
    }

    void SpriteSheet::Play() {
        mIsPaused = false;
    }

    void SpriteSheet::Pause() {
        mIsPaused = true;
    }

    void SpriteSheet::Stop() {
        mIsPaused = true;
        mCurrentFrameIndex = 0;
        SetFrame(mCurrentFrameIndex);
    }

    void SpriteSheet::SetLooped(bool looped) {
        mIsLooped = looped;
    }

    void SpriteSheet::SetColor(const Color& color) {
        mActiveColor = color;
    }

    const Transformation& SpriteSheet::Transform() {
        return mTransform;
    }

	bool SpriteSheet::IsHorizontalFlipped() const
	{
		return mIsHorizontalFlipped;
	}

	bool SpriteSheet::IsLooped() const {
        return mIsLooped;
    }

    bool SpriteSheet::IsPlaying() const {
        return !mIsPaused;
    }

    double SpriteSheet::FrameTime() const {
        return mFrameTime.count();
    }

    void SpriteSheet::SetFrame(uint32_t newFrame, bool resetTime) {
        if (mCurrentAnimation) {
            mAnimationBoundary = mCurrentAnimation->Frame(newFrame);

            SetScale(mTransform.Scale());
        }

        if (resetTime) {
            mCurrentTime = TimeInMSec::zero();
        }
    }

	void SpriteSheet::SetPosition(int32_t offsetX, int32_t offsetY) {
		mTransform.SetPosition(offsetX, offsetY);

		mDestinationRect.x = mTransform.Pos().x - static_cast<int>(mWidth * 0.5F);
		mDestinationRect.y = mTransform.Pos().y - static_cast<int>(mHeight * 0.5F);
	}

	void SpriteSheet::Rotate(float rotate) {
		mTransform.Rotate(rotate);
	}

	void SpriteSheet::SetScale(const Vector2f& scale) {
		mTransform.SetScale(scale);

		mDestinationRect.x = static_cast<int>(mTransform.Pos().x - mWidth * mTransform.Scale().x * 0.5f);
		mDestinationRect.y = static_cast<int>(mTransform.Pos().y - mHeight * mTransform.Scale().y * 0.5f);

		mDestinationRect.w = static_cast<int>(scale.x * mWidth);
		mDestinationRect.h = static_cast<int>(scale.y * mHeight);
	}

    void SpriteSheet::Update(double intervalInMsec) {
        if (!mIsPaused && mCurrentAnimation) {
            mCurrentTime += TimeInMSec(intervalInMsec);

            if (mCurrentTime >= mFrameTime) {
                mCurrentTime = TimeInMSec::zero();

                if ((mCurrentFrameIndex + 1) < mCurrentAnimation->FrameCount()) {
                    mCurrentFrameIndex++;
                }
                else {
                    // Animasyon bitti basa donelim
                    mCurrentFrameIndex = 0;

                    if (!mIsLooped) {
                        mIsPaused = true;
                    }
                }

                // Mevcut animasyon karesini degistirelim
                SetFrame(mCurrentFrameIndex, false);
            }
        }
    }

    void SpriteSheet::Display(SDL_Renderer* renderer, float cameraSpeedRatioX, float cameraSpeedRatioY) const {
		if (nullptr != renderer && nullptr != mCurrentTexture) {
			SDL_Rect displayRect = mDestinationRect;
			displayRect.x -= static_cast<int32_t>(Game::GameCamera().Center().x * cameraSpeedRatioX);
			displayRect.y -= static_cast<int32_t>(Game::GameCamera().Center().y * cameraSpeedRatioY);

            SDL_RenderCopyEx(renderer, mCurrentTexture->Texture(), reinterpret_cast<const SDL_Rect*>(&mAnimationBoundary), &displayRect, mTransform.Rotation(), nullptr, mRenderFlip);
        }
    }
}