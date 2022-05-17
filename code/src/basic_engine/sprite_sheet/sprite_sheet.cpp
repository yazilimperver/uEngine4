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
        , mSpriteBoundary {spriteBoundary.Left, spriteBoundary.Top, spriteBoundary.Width, spriteBoundary.Height }
        , mCurrentFrameIndex{ 0 }
        , mIsPaused{ paused }
        , mIsLooped{ looped }
        , mCurrentTexture{ nullptr } {

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

    Transformation& SpriteSheet::Transform() {
        return mTransform;
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
        }

        if (resetTime) {
            mCurrentTime = TimeInMSec::zero();
        }
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

        // Konum guncellemesi yapalim
        mSpriteBoundary.x = static_cast<int32_t>(mTransform.Pos().x);
        mSpriteBoundary.y = static_cast<int32_t>(mTransform.Pos().y);
    }

    void SpriteSheet::Display(SDL_Renderer* renderer) const {
        if (nullptr != renderer && nullptr != mCurrentTexture) {
            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0x80);
            
            if (mDrawBoundary){
                SDL_RenderFillRect(renderer, &mSpriteBoundary);
            }

            // Flip bilgisine bakmamiz gerekebilir
            SDL_RenderCopyEx(renderer, mCurrentTexture->Texture(), reinterpret_cast<const SDL_Rect*>(&mAnimationBoundary), &mSpriteBoundary, 0, nullptr, SDL_FLIP_NONE);
        }
    }
}