/**
 * @file map_view.h.
 * @date 18.08.2022
 * @author Yazilimperver
 * @brief Cografik bir harita gorunumunu ifade etmek icin kullanacagimiz sinif.
 *		  Sinif temel olcek, ekran/cografik kordinat donusumundan sorumludur.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include "common.h"

#include "geo_point.h"
#include "tile_tms.h"

namespace gis {
	class MapView {
	public:
		MapView(uint32_t winWidth, uint32_t winHeight, 
			GeoPoint viewCenter = { 39.0, 36.0 }, 
			uint32_t zoomLevel = 0);

		std::string InfoText();

		void MoveInPixel(int32_t x, int32_t y);
		const TileTms& ObtainTileTms() const;
		
		void SetCenterInPixel(const PointInPixels& center);
		const PointInPixels& CenterInPixels() const;
		const PointInMeters& CenterInMeter() const;
		GeoPoint CenterInGeographic() const;
		
		uint32_t WinWidth() const;
		uint32_t WinHeight() const;

		void SetZoomLevel(uint32_t zoom);
		uint32_t ZoomLevel() const;
		
		double Scale() const;
		
		double Resolution() const;

		void SetRotation(double rotInAngle);
		double Rotation() const;
		GeoPoint ToGeographic(const PointInPixels screenCoordinate) const;
		PointInPixels ToScreen(const GeoPoint geographicPoint) const;
	private:
		void UpdateCenter();
		double mRotation{ 0 };
		uint32_t mWinWidth{640};
		uint32_t mWinHeight{480};
		uint32_t mZoomLevel{0};
		uint32_t mDPI{ 120 };
		GeoPoint mGeogViewCenter{ 0, 0 };

		/** @brief   Ekran sol ust kosesinin piksel karsiligi */
		PointInPixels mWindowTopLeftInPixels{ 0, 0 };
		PointInPixels mViewCenterInPixels{ 0, 0 };
		PointInMeters mViewCenterInMeter{0, 0};
		TileTms mCenterTmsTile;
	};
}

#endif // !MAP_VIEW_H

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
