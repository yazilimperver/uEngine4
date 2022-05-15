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
        explicit SpriteSheet(std::string_view spriteSheetConfig, bool paused = false, bool looped = true);
        
        void Initialize();
        void Update(double deltaTimeInMsec);
        void Display(SDL_Renderer* renderer) const;

        void SetAnimation(std::string_view animationLabel);
        
        /** @brief Animasyon kontrol API'leri */
        void Play();
        void Pause();
        void Stop();
        void SetLooped(bool looped);

        bool IsLooped() const;
        bool IsPlaying() const;
        void SetFrame(uint32_t newFrame, bool resetTime = true);
        double FrameTime() const;

        void SetColor(const Color& color);

        Transformation& Transform();
    private:
        std::optional<SpriteSheetParameters> ParseConfigFile(const std::string& config);

        Transformation mTransform;
        std::string mSpriteSheetConfig;
        std::string mCurrentAnimationLabel;

        SDL_Rect mSpriteBoundary;
        Rectangle<int32_t> mAnimationBoundaary;

        //! Reference to current animation
        Color mActiveColor;
        const Animation* mCurrentAnimation;
        TimeInMSec mFrameTime{ 0 };
        TimeInMSec mCurrentTime{ 0 };
        uint32_t mCurrentFrameIndex{0};

        bool mIsPaused;
        bool mIsLooped;
        const SdlTextureAsset* mCurrentTexture;
        SpriteSheetParameters mLastUsedParameters;

        /** @brief Animasyon etiketlerine gore anahtarlanan animasyonlar*/
        std::unordered_map<std::string, std::unique_ptr<Animation>> mLoadedAnimations;

        /** @brief Spritesheet'ler icin kullanilacak olan texture'lar */
        std::unordered_map<std::string, SdlTextureAsset*> mTextureList;
    };
}
#endif // UANIMATEDSPRITE_H__