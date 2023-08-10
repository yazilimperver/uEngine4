/**
 * @file   geometry_type.h
 * @date   4/23/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_GEOMETRY_TYPE_H
#define INC_GEOMETRY_TYPE_H

#include <cstdint>

namespace gl {
    /** @brief   GDAL benzeri kutuphaneler icin kullanilabilecek 2b/2.5B geometri tipleri */
    enum class GeometryType : uint32_t {
		eGT_UNKNOWN = 0,
		eGT_POINT = 1,
		eGT_LINESTRING = 2,
		eGT_POLYGON = 3,
		eGT_MULTIPOINT = 4,
		eGT_MULTILINESTRING = 5,
		eGT_MULTIPOLYGON = 6,
		eGT_GEOMETRYCOLLECTION = 7,
		eGT_NONE = 100,
		eGT_LINEARRING = 101,
		eGT_POINT2D = 0X80000001,
		eGT_LINESTRING25D = 0X80000002,
		eGT_POLYGON25D = 0X80000003,
		eGT_MULTIPOINT25D = 0X80000004,
		eGT_MULTILINESTRING25D = 0X80000005,
		eGT_MULTIPOLYGON25D = 0X80000006,
		eGT_GEOMETRYCOLLECTION2D = 0X80000007
    };
}

#endif	// INC_GEOMETRY_TYPE_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

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


