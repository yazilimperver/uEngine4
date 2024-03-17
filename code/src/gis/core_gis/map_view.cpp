#include "map_view.h"

#include "slippy_map_util.h"
#include "fmt/format.h"

namespace gis {
	MapView::MapView(uint32_t winWidth, uint32_t winHeight, GeoPoint viewCenter, uint32_t zoomLevel)
		: mWinWidth{ winWidth }
		, mWinHeight{ winHeight }
		, mGeogViewCenter{ viewCenter }
		, mZoomLevel{ zoomLevel }
		, mCenterTmsTile{ TileTms::GeographicToTile(viewCenter, zoomLevel) }{		
		SetZoomLevel(zoomLevel);
		mViewCenterInPixels = SlippyMapUtil::GeographicToPixel(mGeogViewCenter, mZoomLevel);
	}

	void MapView::SetZoomLevel(uint32_t zoom) {
		mZoomLevel = zoom; 
		mCenterTmsTile = TileTms::GeographicToTile(mGeogViewCenter, mZoomLevel);
		mViewCenterInPixels = SlippyMapUtil::GeographicToPixel(mGeogViewCenter, mZoomLevel);
		mViewCenterInMeter = SlippyMapUtil::PixelToMeter(mViewCenterInPixels, mZoomLevel);
		
		mWindowTopLeftInPixels.x = mViewCenterInPixels.x - (mWinWidth / 2);
		mWindowTopLeftInPixels.y = mViewCenterInPixels.y - (mWinHeight / 2);
	}

	uint32_t MapView::ZoomLevel() const {
		return mZoomLevel;
	}

	double MapView::Scale() const {
		return GisMetaData::Scale(mZoomLevel, mDPI);
	}

	double MapView::Resolution() const {
		return GisMetaData::Resolution(mZoomLevel);
	}

	void MapView::SetRotation(double rotInAngle) {
		mRotation = rotInAngle;
	}

	double MapView::Rotation() const {
		return mRotation;
	}

	PointInPixels MapView::ToScreen(const GeoPoint geographicPoint) const {
		PointInPixels pixelCoord = SlippyMapUtil::GeographicToPixel(geographicPoint, mZoomLevel);
		return (pixelCoord - mWindowTopLeftInPixels);
	}

	GeoPoint MapView::ToGeographic(const PointInPixels screenCoordinate) const {
		PointInPixels pixelCoord = mWindowTopLeftInPixels + screenCoordinate;
		return SlippyMapUtil::PixelToGeographic(pixelCoord, mZoomLevel);
	}

	void MapView::UpdateCenter() {

		mGeogViewCenter = SlippyMapUtil::PixelToGeographic(mViewCenterInPixels, mZoomLevel);
		mViewCenterInMeter = SlippyMapUtil::PixelToMeter(mViewCenterInPixels, mZoomLevel);
		mCenterTmsTile = TileTms::PixelToTile(mViewCenterInPixels, mZoomLevel);
		mWindowTopLeftInPixels.x = mViewCenterInPixels.x - (mWinWidth / 2);
		mWindowTopLeftInPixels.y = mViewCenterInPixels.y - (mWinHeight / 2);
	}

	void MapView::MoveInPixel(int32_t x, int32_t y)	{
		mViewCenterInPixels.x += x;
		mViewCenterInPixels.y += y;
		UpdateCenter();
	}
	
	const TileTms& MapView::ObtainTileTms() const {
		return mCenterTmsTile;
	}

	void MapView::SetCenterInPixel(const PointInPixels& center) {
		mViewCenterInPixels.x = center.x;
		mViewCenterInPixels.y = center.y;
		UpdateCenter();
	}

	const PointInPixels& MapView::CenterInPixels() const {
		return mViewCenterInPixels;
	}

	const PointInMeters& MapView::CenterInMeter() const	{
		return mViewCenterInMeter;
	}

	GeoPoint MapView::CenterInGeographic() const {
		return mGeogViewCenter;
	}

    GeoRectangle MapView::GeographicBoundary() const {        
        auto center = mViewCenterInPixels;
        center.x -= (mWinWidth / 2);
        center.y += (mWinHeight/2);
        auto guneyBati = SlippyMapUtil::PixelToGeographic(center, mZoomLevel);

        center.x += (mWinWidth);
        center.y -= (mWinHeight);
        auto kuzeyDogu = SlippyMapUtil::PixelToGeographic(center, mZoomLevel);

        return GeoRectangle{ guneyBati, kuzeyDogu };
    }

    bool MapView::IsInside(const PointInPixels& point) const {
        return (point.x > 0)
            && (point.x < mWinWidth)
            && (point.y < mWinHeight)
            && (point.y > 0);
    }

	uint32_t MapView::WinWidth() const {
		return mWinWidth;
	}

	uint32_t MapView::WinHeight() const {
		return mWinHeight;
	}

	std::string MapView::InfoText() {
		auto output = fmt::format("Geog. Cntr : <{:07.3f}, {:07.3f}>\nPixel Cntr : <{}, {}>\nMeters Cntr: <{:09.1f}, {:09.1f}>\nTMSTile    : <{}, {}>\nGoogleTile : <{}, {}>\nZoom Level : <{}>"
			, mGeogViewCenter.Latitude(), mGeogViewCenter.Longitude()
			, mViewCenterInPixels.x, mViewCenterInPixels.y
			, mViewCenterInMeter.x, mViewCenterInMeter.y
			, mCenterTmsTile.TileInfo().x, mCenterTmsTile.TileInfo().y
			, mCenterTmsTile.ObtainGoogleTileInfo().x, mCenterTmsTile.ObtainGoogleTileInfo().y
			, mZoomLevel);

		return output;
	}
}