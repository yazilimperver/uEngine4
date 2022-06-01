/**
 * @file animated_tile.h.
 * @date 1.06.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include <vector>
#include <memory>
#include <cstdint>

#include "basic_engine/sprite.h"

namespace basic_engine {
	struct AnimatedTile {
		/** @brief Ilgili animasyondaki her bir kare icin olusturulan sprite */
		std::vector<std::unique_ptr<basic_engine::Sprite>> FrameSprites;

		/** @brief Ilgili animasyon karesi icin planlanan sure */
		std::vector<double> FrameTimesInMsec;
		uint32_t ActiveFrame{ 0 };

		/** @brief En son animasyon karesi degisiminden bu yana gecen sure */
		double ElapsedTime{ 0.0 };
	};
}

#endif // !ANIMATED_TILE_H

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
