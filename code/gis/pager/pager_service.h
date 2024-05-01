/**
 * @file pager_service.h.
 * @date 28.08.2022
 * @author Yazilimperver
 * @brief Pafta yukleyicilere iliskin disariya sunulacak olan temel servisler
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef PAGER_SERVICE_H
#define PAGER_SERVICE_H

#include <vector>

#include "core_gis/common.h"

#include "geo_tile.h"

namespace gis {
	class PagerService {
	public:
		/** @brief Yuklenecek paftalar icin referans alinacak konum */
		virtual void UpdateReference(const PointInPixels& newCenter, uint32_t zoomLevel) = 0;

		/** @brief Su an icin gorunur ekran bulunan paftalar  */
		virtual const std::vector<TileId>& ActiveTiles() const = 0;
	};
}

#endif // !PAGER_SERVICE_H

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
