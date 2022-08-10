/**
 * @file tile_layer.h.
 * @date 30.05.2022
 * @author Yazilimperver
 * @brief  Paftalari iceren pafta katmanini temsil eden siniftir.
 * @todo   Ölçceklendirme, dondurme ve flip vb hususlarýný ekleyeceðiz		  
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef TILE_LAYER_H_
#define TILE_LAYER_H_

#include <cstdint>
#include <vector>
#include <memory>
#include <string_view>

#include "layer.h"

#include "basic_engine/sprite.h"

#include "animated_tile.h"

namespace tson {
	class Layer;
}

namespace basic_engine {

	/**
	 * @class TileLayer
	 * @brief Bu katman paftalara gore cizim yapilacak katmanlari temsilen kullanilacaktir,
	 */
	class TileLayer : public Layer {
	public:
		TileLayer(std::string_view rootPath, tson::Layer& layer);
		virtual void Update(double deltaTimeInMsec);
		virtual void Display(SDL_Renderer* renderer) const ;
	private:

		/** @brief Animasyon iceren paftalara iliskin kontrolleri gerceklestirelim */
		void CheckTileAnimation(auto& animatedTile, double deltaTimeInMsec);

		/** @brief Sabit ve animasyon icermeyen paftalar */
		std::vector<std::unique_ptr<basic_engine::Sprite>> mNonAnimatedSprites;
		
		/** @brief Animasyon iceren paftalar */
		std::vector<AnimatedTile> mAnimatedSprites;
	};
}

#endif // !TILE_LAYER_H_

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
