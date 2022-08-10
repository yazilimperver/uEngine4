/**
 * @file sprite_sheet_serializer.h.
 * @date 15.05.2022
 * @author Yazilimperver
 * @brief Spritesheet ve animasyon JSON parametrelerini anlamlandirmak icin kullanilacak olan siniftir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SPRITESHEETSERIALIZER_H_
#define SPRITESHEETSERIALIZER_H_

#include "animation_parameters.h"
#include "sprite_sheet_parameters.h"

#include "basic_engine/rectangle_serializer.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp> // std::pair icin

namespace basic_engine {
	/**@brief AnimationParameters sinifi icin kullanilacak olan serializer */
	template<class Archive>
	void serialize(Archive& archive, basic_engine::AnimationParameters& m) {
		archive(cereal::make_nvp("AnimationName", m.AnimationName),
			cereal::make_nvp("TextureName", m.TextureName),
			cereal::make_nvp("Frames", m.AnimationFrames));
	}

	/**@brief SpriteSheetParameters sinifi icin kullanilacak olan serializer */
	template<class Archive>
	void serialize(Archive& archive, basic_engine::SpriteSheetParameters& m) {
		archive(cereal::make_nvp("FrameTime", m.FrameTime),
			cereal::make_nvp("InitialAnimation", m.InitialAnimation),
			cereal::make_nvp("Textures", m.TextureFiles),
			cereal::make_nvp("Animations", m.Animations));
	}
}
#endif // !SPRITESHEETSERIALIZER_H_

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
