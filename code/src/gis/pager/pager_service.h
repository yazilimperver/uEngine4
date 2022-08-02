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

		/** @brief Pager tarafindan yuklenen paft */
		virtual const std::vector<TileId>& ActiveTiles() = 0;
	};
}

#endif // !PAGER_SERVICE_H

