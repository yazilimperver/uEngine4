#include "map_view.h"

#include "slippy_map_util.h"
#include "fmt/core.h"

namespace gis {
	MapView::MapView(uint32_t winWidth, uint32_t winHeight, GeoPoint viewCenter, uint32_t zoomLevel)
		: mWinWidth{ winWidth }
		, mWinHeight{ winHeight }
		, mGeogViewCenter{ viewCenter }
		, mZoomLevel{ zoomLevel }
		, mTileTmz{ TileTmz::GeographicToTile(viewCenter, zoomLevel) }{
		mViewCenterInPixels = SlippyMapUtil::GeographicToPixel(mGeogViewCenter, mZoomLevel);
		mViewCenterInMeter = SlippyMapUtil::PixelToMeter(mViewCenterInPixels, mZoomLevel);
	}

	void MapView::MoveInPixel(int32_t x, int32_t y)
	{
		mViewCenterInPixels.x += x;
		mViewCenterInPixels.y += y;

		mGeogViewCenter = SlippyMapUtil::PixelToGeographic(mViewCenterInPixels, mZoomLevel);
		mViewCenterInMeter = SlippyMapUtil::PixelToMeter(mViewCenterInPixels, mZoomLevel);
		mTileTmz = TileTmz::PixelToTile(mViewCenterInPixels, mZoomLevel);
	}

	std::string MapView::InfoText() {
		auto output = fmt::format("Geog. Center: <{}, {}>\nZoom Level: {}\nPixel Center: <{}, {}>\nMeters Center: <{}, {}>\nTmz Tile: <{}, {}>\nGoogle tile: <{}, {}>"
			, mGeogViewCenter.Latitude(), mGeogViewCenter.Longitude()
			, mZoomLevel
			, mViewCenterInPixels.x, mViewCenterInPixels.y
			, mViewCenterInMeter.x, mViewCenterInMeter.y
			, mTileTmz.TileInfo().x, mTileTmz.TileInfo().y
			, mTileTmz.ObtainGoogleTileInfo().x, mTileTmz.ObtainGoogleTileInfo().y);

		return output;
	}
}