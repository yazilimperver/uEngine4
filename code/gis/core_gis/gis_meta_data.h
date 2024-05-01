/**
 * @file gis_meta_data.h.
 * @date 26.06.2022
 * @author Yazilimperver
 * @brief Bazi temel CBS sabitlerini simdilik burada tutalim bunlarin bir kismini ileride siniflara dagitiyor olacagiz
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GIS_META_DATA_H_
#define GIS_META_DATA_H_

#include "common.h"

namespace gis {	
	constexpr double cEarthRadiusInMeter = 6378137.0;
	constexpr double cEquatorLengthInMeter = 2.0 * PI * cEarthRadiusInMeter;
	constexpr double cEquatorLengthInKm = cEquatorLengthInMeter / 1000.0;
	constexpr double cOriginShift = cEquatorLengthInMeter / 2.0;

	constexpr auto cDefaultTileSize = 256;

	constexpr double cLevel0Resolution = cEquatorLengthInMeter / cDefaultTileSize;

		class GisMetaData {
		public:
			/** @brief Verilen zoom seviyesine gore, ilgili cozunurluk (m/px) donulur */
			static constexpr double Resolution(uint32_t zoomLevel = 0) {
				return cLevel0Resolution / (1 << zoomLevel);
			}	

			/** @brief Verilen cozunurluk ve DPI'a gore olcek (ekrandaki 1cm haritadaki 1cm nasil map ediyor 
					   Ref: https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames#Resolution_and_Scale*/
			static constexpr double Scale(uint32_t zoomLevel = 0, uint32_t dpi = 120) {
				return dpi *  1 / 0.0254 * cLevel0Resolution / (1 << zoomLevel);
			}
	};
}

#endif // !GIS_META_DATA_H_

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
