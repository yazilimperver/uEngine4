#include "animation.h"

#include "sdl_asset/sdl_texture_asset.h"

namespace basic_engine {
    Animation::Animation(std::string_view animationName, const std::vector<Rectangle<int32_t>>& frames, const SdlTextureAsset* texture)
        : mAnimationName{ animationName.data() }
        , mFrames{ frames }
        , mTexture{ texture }
    {
    }

    const SdlTextureAsset* Animation::SpriteSheet() const {
        return mTexture;
    }

    uint32_t Animation::FrameCount() const {
        return static_cast<uint32_t>(mFrames.size());
    }

    const Rectangle<int32_t>& Animation::Frame(uint32_t n) const {
        return mFrames[n];
    }
}