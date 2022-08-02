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
}

#endif // !TILE_ID_H

