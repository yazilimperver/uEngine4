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
