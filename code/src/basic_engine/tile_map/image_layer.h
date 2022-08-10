/**
 * @file image_layer.h.
 * @date 10.08.2022
 * @author Yazilimperver
 * @brief Tiled tarafindan uretilen resim katmanlarini temsil eden siniftir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef IMAGE_LAYER_H_
#define IMAGE_LAYER_H_

#include <cstdint>
#include <memory>
#include <string_view>

#include "layer.h"

#include "basic_engine/sprite.h"

namespace tson {
	class Layer;
}

namespace basic_engine {
	class ImageLayer : public Layer {
	public:
		ImageLayer(std::string_view rootPath, tson::Layer& layer);
		virtual void Update(double deltaTimeInMsec) override;
		virtual void Display(SDL_Renderer* renderer) const override;
	protected:
		std::unique_ptr<basic_engine::Sprite> mSprite;
		int32_t mImageWidth{0};

		bool mIsRepeatXEnabled{ false };
		bool mIsRepeatYEnabled{ false };
		float mParallaxFactorX{1.0F};
		float mParallaxFactorY{1.0F};
	};
}

#endif // !IMAGE_LAYER_H_

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
