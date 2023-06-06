/**
 * @file tile_map.h.
 * @date 21.05.2022
 * @author Yazilimperver
 * @brief Tiled uygulamasi tarafindan olusturulan .json formatindaki tilemap verilerini okumak icin kullanilacak siniftir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <string_view>
#include <memory>
#include <vector>
#include <map>

#include "SDL.h"

#include "extras/pocketlzma.hpp"
#include "tileson.hpp"

#include "graphics/color.h"

#include "basic_engine/common.h"

#include "layer.h"

namespace tson {
	class Map;
	class Layer;
	class Animation;
}

namespace basic_engine {
	class TileMap {
	public:
		TileMap(std::string_view rootPath, std::string_view tileMapFile);
		bool Initialize();
		void InitializeObjectLayer(tson::Layer& layer);
		void InitializeTileLayer(tson::Layer& layer);
		void InitializeImageLayer(tson::Layer& layer);
		void Update(double deltaTimeInMsec);
		void Display(SDL_Renderer* renderer) const;
	protected:
		std::string GetPath(std::string_view assetPath);

		std::string mRootPath{ "./tilemap/example/" };
		Color mBackgroundColor;
		std::string mTileMapFile;
		std::unique_ptr<tson::Map> mTileMap;

		std::string mTileSprites;
		std::map<uint32_t, tson::Animation*> m_animationUpdateQueue;

		std::vector<std::unique_ptr<Layer>> mDisplayLayers;

		// Used for world related stuff
		Vector2i m_positionOffset{ 0,0 };
	};
}

#endif // !TILEMAP_H_

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
