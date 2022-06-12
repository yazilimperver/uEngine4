/**
 * \file    sprite_sheet.h
 * \date    2018/01/27
 * \author  developer
 * \brief   This class is responsible for playing animations which can be preregistered or set at the runtime
 * Copyright © 2017, uEngine V3.1 Mehmet Fatih ULUAT <fatihuluat@gmail.com>
 */

#ifndef SPRITESHEET_H__
#define SPRITESHEET_H__

#include <chrono>
#include <unordered_map>

#include "SDL.h"

#include "graphics/color.h"

#include "basic_engine/rectangle.h"
#include "basic_engine/transformation.h"

#include "common.h"
#include "animation.h"
#include "sprite_sheet_parameters.h"

namespace basic_engine {
    class SdlTextureAsset;
    using TimeInMSec = std::chrono::duration<double, std::ratio<1, 1000>>;

    class SpriteSheet  {
    public:
        explicit SpriteSheet(std::string_view spriteSheetConfig, const Rectangle<int32_t>& spriteBoundary, bool paused = false, bool looped = true);

        /** @brief Ilklendirme sonucu donulecektir. */
        bool Initialize();
        void Update(double deltaTimeInMsec);
        void Display(SDL_Renderer* renderer, float cameraSpeedRatioX = 1.0F, float cameraSpeedRatioY = 1.0F) const;

        void SetAnimation(std::string_view animationLabel);
        
        /** @brief Animasyon kontrol API'leri */
        void Play();
        void Pause();
        void Stop();
        void SetLooped(bool looped);

        bool IsLooped() const;
        bool IsPlaying() const;
        void SetFrame(uint32_t newFrame, bool resetTime = true);
        void SetPosition(int32_t offsetX, int32_t offsetY);
        void Rotate(float rotate);
        void SetScale(const Vector2f& scale);
        double FrameTime() const;

        void SetColor(const Color& color);

        const Transformation& Transform();

        bool IsHorizontalFlipped() const;
        void EnableHorizontalFlipped();
        bool IsVerticalFlipped() const;
        void EnableVerticalFlipped();
        void DisableFlip();
    private:
        std::optional<SpriteSheetParameters> ParseConfigFile(const std::string& config);

        Transformation mTransform;
        std::string mSpriteSheetConfig;
        std::string mCurrentAnimationLabel;

        bool mIsHorizontalFlipped;
        bool mIsVerticalFlipped;
        SDL_RendererFlip mRenderFlip{ SDL_FLIP_NONE };

        /** @brief Cizim icin kullanilacak kutu */
        SDL_Rect mDestinationRect;

		/** @brief Mevcut animasyon dokusunun yukseklik ve genisligi */
		int32_t mHeight;
		int32_t mWidth;
        Rectangle<int32_t> mAnimationBoundary{0, 0, 0, 0};

        //! Reference to current animation
        Color mActiveColor;
        const Animation* mCurrentAnimation{nullptr};
        TimeInMSec mFrameTime{ 0 };
        TimeInMSec mCurrentTime{ 0 };
        uint32_t mCurrentFrameIndex{0};

        bool mIsPaused{false};
        bool mIsLooped{false};
        bool mDrawBoundary{ false };
        const SdlTextureAsset* mCurrentTexture;
        SpriteSheetParameters mLastUsedParameters;

        /** @brief Animasyon etiketlerine gore anahtarlanan animasyonlar*/
        std::unordered_map<std::string, std::unique_ptr<Animation>> mLoadedAnimations;

        /** @brief Spritesheet'ler icin kullanilacak olan texture'lar */
        std::unordered_map<std::string, SdlTextureAsset*> mTextureList;
    };
}
#endif // UANIMATEDSPRITE_H__