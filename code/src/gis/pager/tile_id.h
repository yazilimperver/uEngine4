/**
 * @file tile_id.h.
 * @date 3.07.2022
 * @author Yazilimperver
 * @brief Paftalari tanimlamak icin kullanilacak veri yapisi
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef TILE_ID_H
#define TILE_ID_H

#include <cstdint>

#include "utility/less_by_pairs.h"

namespace gis {

	struct TileId {
		int32_t TileX{ 0 };
		int32_t TileY{ 0 };
		uint32_t ZoomLevel{ 0 };

		TileId() {
		}

		TileId(int32_t tileX, int32_t tileY, uint32_t zoomLevel) {
			TileX = tileX;
			TileY = tileY;
			ZoomLevel = zoomLevel;
		}

		/** @brief Artik bu veri yapisini map ve unordered_map tarzi konteynerlerde kullanabiliriz */
		bool operator<(const TileId& r) {
			return LessByPairs(ZoomLevel, r.ZoomLevel, TileX, r.TileX, TileY, r.TileY);
		}

		friend bool operator== (const TileId& left, const TileId& right);
		friend bool operator!= (const TileId& left, const TileId& right);
	};

	inline bool operator== (const TileId& left, const TileId& right) {
		return (left.TileX == right.TileX &&
			left.TileY == right.TileY &&
			left.ZoomLevel == right.ZoomLevel);
	}

	inline bool operator!= (const TileId& left, const TileId& right) {
		return (left.TileX != right.TileX ||
			left.TileY != right.TileY ||
			left.ZoomLevel != right.ZoomLevel);

	}

	class TileIdHashFunction {
	public:
		size_t operator()(const TileId& tile) const {
			return static_cast<size_t>(pow(2, tile.ZoomLevel) * tile.TileY + tile.TileX);
		}
	};
}

#endif // !TILE_ID_H

