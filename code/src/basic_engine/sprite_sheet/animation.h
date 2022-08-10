/**
 * @file animation.h.
 * @date 13.05.2022
 * @author Yazilimperver
 * @brief Spritesheet animasyonu icin kullanilacak olan temel animasyon sinifidir.
 * 		  Her bir animasyon, birdee fazla frame icerir ve spritesheet de birden fazla animasyon icerebilir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ANIMATION_H__
#define ANIMATION_H__

#include <vector>
#include <memory>
#include <string_view>

#include "basic_engine/rectangle.h"
#include "common.h"

namespace basic_engine {
    class SdlTextureAsset;

	class Animation {
    public:
        Animation(std::string_view animationName, 
                  const std::vector<Rectangle<int32_t>>& frames, 
                  const SdlTextureAsset* texture);

        const SdlTextureAsset* SpriteSheet() const;
        uint32_t FrameCount() const;
        const Rectangle<int32_t>& Frame(uint32_t n) const;
    protected:
        std::string mAnimationName;
        std::vector<Rectangle<int32_t>> mFrames;
        const SdlTextureAsset* mTexture{nullptr};
	};
}

#endif // ANIMATION_H__

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
