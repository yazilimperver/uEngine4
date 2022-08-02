#ifndef GEO_TILE_H
#define GEO_TILE_H

#include <cstdint>

#include "core_gis/common.h"
#include "basic_engine/rectangle.h"

#include "tile_id.h"

namespace basic_engine {
	class Asset;
}

namespace gis {
	struct GeoTile {
		TileId mID{ -1, -1 };
		basic_engine::Rectangle<int32_t> mBoundary;
		basic_engine::Asset* mData{ nullptr };
	};
}

#endif // !GEO_TILE_H

