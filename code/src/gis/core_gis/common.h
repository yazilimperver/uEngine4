/**
 * @file common.h.
 * @date 18.08.2022
 * @author Yazilimperver
 * @brief  CBS genelinde kullanýlacak olan bir takým sabit ve kütüphaneler
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef CORE_GIS_COMMON_H
#define CORE_GIS_COMMON_H

#include <cmath>
#include <tuple>

#include "glm/glm.hpp"

#include "geo_point.h"

constexpr double PI = 3.14159265358979323846;                        
constexpr double PI_2 = 1.57079632679489661923;
constexpr double PI_4 = 0.785398163397448309616;

constexpr auto DegToRadian(const double degrees) {
    return degrees * (PI / 180.0);
}

constexpr auto RadianToDeg(const double radians) {
    return radians * (180 / PI);
}

typedef glm::tvec2<double>   PointInMeters;
typedef glm::tvec2<int32_t>  PointInPixels;
typedef glm::tvec2<int32_t>  TmsTileInfo;
typedef glm::tvec2<int32_t>  GoogleTileInfo;

typedef std::tuple<gis::GeoPoint, gis::GeoPoint> GeoRectangle;
typedef std::tuple<PointInMeters, PointInMeters> MercatorRectangle;
typedef std::tuple<PointInPixels, PointInPixels> PixelRectangle;

#endif // !CORE_GIS_COMMON_H

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
