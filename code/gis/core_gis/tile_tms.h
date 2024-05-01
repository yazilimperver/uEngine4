/**
 * @file tile_tmz.h.
 * @date 18.08.2022
 * @author Yazilimperver
 * @brief TMS paftalarýný temsil eden sýnýftýr
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef TILE_TMS_H
#define TILE_TMS_H

#include <cstdint>
#include <cmath>
#include <string>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <sstream>

#include "common.h"
#include "gis_meta_data.h"
#include "slippy_map_util.h"
#include "tile_tms.h"

#include "geo_point.h"

namespace gis {
	class TileTms {
	public:
        static TileTms FromTmsTileInfo(const TmsTileInfo& tmsTileInfo, uint32_t zoom);

        static TileTms FromGoogleTile(const GoogleTileInfo& googleTile, uint32_t  zoom);
        
        // Return tile for given Microsoft QuadTree
        static TileTms QuadTreeToTile(const std::string& quadTree);
        
        // Returns tile for given geographic coordinates
        static TileTms GeographicToTile(const GeoPoint& pointInGeog, uint32_t  zoom);
        
        // Returns tile for given mercator coordinates
        static TileTms MeterToTile(const PointInMeters& pointInMeter, uint32_t  zoom);

        // Returns a tile covering region in given pixel coordinates
        static TileTms PixelToTile(const PointInPixels& inputInPixel, uint32_t  zoom);

        // Returns bounds of the given tile in EPSG: 3857 coordinates
        MercatorRectangle MercatorBounds();

        // Returns bounds of the given tile in latutude/longitude using WGS84 datum
        GeoRectangle GeographicBounds();

        // Returns bounds of the given tile in pixels
        PixelRectangle PixelBounds() const;
        PixelRectangle PixelBoundsTopLeftBottomRigth() const;
        
        // Returns the center of tile
        PointInPixels PixelCenter() const;
        
        // Obtain tms tile info
        TmsTileInfo TileInfo() const;

        // Converts TMS tile coordinates to Google Tile coordinates
        GoogleTileInfo ObtainGoogleTileInfo() const;

        // Converts TMS tile coordinates to Microsoft QuadTree
        std::string QuadTreeRepresentation() const;
        
        uint32_t Zoom() const;
        int32_t TmsX() const;
        int32_t TmsY() const;
	private:
        TileTms(int32_t tmsX, int32_t tmsY, uint32_t zoom);

		int32_t mTmsX{0};
		int32_t mTmsY{0};
		uint32_t mZoom{0};
	};
}

#endif // !TILE_TMS_H

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
