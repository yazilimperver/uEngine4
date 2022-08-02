#ifndef TILE_TMZ_H
#define TILE_TMZ_H

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
#include "tile_tmz.h"

#include "geo_point.h"

namespace gis {
	class TileTmz {
	public:
        static TileTmz FromTmsTileInfo(const TmsTileInfo& tmsTileInfo, uint32_t zoom);

        static TileTmz FromGoogleTile(const GoogleTileInfo& googleTile, uint32_t  zoom);
        
        // Return tile for given Microsoft QuadTree
        static TileTmz QuadTreeToTile(const std::string& quadTree);
        
        // Returns tile for given geographic coordinates
        static TileTmz GeographicToTile(const GeoPoint& pointInGeog, uint32_t  zoom);
        
        // Returns tile for given mercator coordinates
        static TileTmz MeterToTile(const PointInMeters& pointInMeter, uint32_t  zoom);

        // Returns a tile covering region in given pixel coordinates
        static TileTmz PixelToTile(const PointInPixels& inputInPixel, uint32_t  zoom);

        // Returns bounds of the given tile in EPSG: 3857 coordinates
        MercatorRectangle MercatorBounds();

        // Returns bounds of the given tile in latutude/longitude using WGS84 datum
        GeoRectangle GeographicBounds();
        
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
        TileTmz(int32_t tmsX, int32_t tmsY, uint32_t zoom);

		int32_t mTmsX{0};
		int32_t mTmsY{0};
		uint32_t mZoom{0};
	};
}

#endif // !TILE_TMZ_H

