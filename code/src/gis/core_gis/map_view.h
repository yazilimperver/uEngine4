#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include "common.h"

#include "geo_point.h"
#include "tile_tmz.h"

namespace gis {
	class MapView {
	public:
		MapView(uint32_t winWidth, uint32_t winHeight, 
			GeoPoint viewCenter = { 39.0, 36.0 }, 
			uint32_t zoomLevel = 0);

		void MoveInPixel(int32_t x, int32_t y);
		std::string InfoText();
	private:
		uint32_t mWinWidth{640};
		uint32_t mWinHeight{480};
		uint32_t mZoomLevel{0};
		GeoPoint mGeogViewCenter{ 0, 0 };
		PointInPixels mViewCenterInPixels{ 0, 0 };
		PointInMeters mViewCenterInMeter{0, 0};
		TileTmz mTileTmz;
	};
}

#endif // !MAP_VIEW_H
