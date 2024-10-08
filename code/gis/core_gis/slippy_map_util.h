/**
 * @file slippy_map_util.h.
 * @date 26.06.2022
 * @author Yazilimperver
 * @brief  Temel co�rafik konum/piksel/metre d�n���mleri icin kullanabilece�imiz fonksiyonlar� icerisinde bar�nd�ran s�n�ft�r
 * 		   ref: https://www.maptiler.com/google-maps-coordinates-tile-bounds-projection/#3/15.00/50.00
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SLIPPY_MAP_UTIL_H
#define SLIPPY_MAP_UTIL_H

#include "common.h"

#include "geo_point.h"
#include "gis_meta_data.h"

namespace gis {
	class SlippyMapUtil {
	public: 
		// Converts pixel coordinates in given zoom level of pyramid to geographic
		static GeoPoint PixelToGeographic(const PointInPixels& inputInPixels, uint32_t zoomLevel);

		// Converts pixel coordinates in given zoom level of pyramid to EPSG: 3857
		static PointInMeters PixelToMeter(const PointInPixels& inputInPixels, uint32_t zoomLevel);

		// Converts XY point from Spherical Mercator EPSG: 3857 to lat/lon in WGS84 Datum
		static GeoPoint MeterToGeographic(const PointInMeters& inputInMeters);

		// Converts EPSG:3857 to pyramid pixel coordinates in given zoom level
		static PointInPixels MeterToPixels(const PointInMeters& inputInMeters, uint32_t zoomLevel);

		// Converts given lat/lon in WGS84 Datum to XY in Spherical Mercator EPSG: 3857
		static PointInMeters GeographicToMeters(const GeoPoint& inputInGeog);

		// Convert given geogprahic position to pixel wrt given zoom level
		static PointInPixels GeographicToPixel(const GeoPoint& inputInGeog, uint32_t zoomLevel);

		static GeoPoint GetGeographic(double latitude, double longitude);

		// Convert meters as signed wrt to center of world
		static PointInMeters GetSignedMeters(const PointInMeters& inputInMeters, const PointInPixels& inputInPixel, uint32_t zoomLevel);
	};
}

#endif // !SLIPPY_MAP_UTIL_H

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
