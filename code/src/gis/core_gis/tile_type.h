/**
 * @file   tile_type.h
 * @date   5/20/2023
 * @author Yazilimperver
 * @brief  Detaylar icin https://gis.stackexchange.com/questions/132242/what-are-the-differences-between-tms-xyz-wmts
 * @remark
 */

#ifndef INC_TILE_TYPE_H
#define INC_TILE_TYPE_H

#include <cstdint>

namespace gis {
    enum class TileType {
        XYZ, // Google vb paftalarin numaralandirma yontemi
        TMS, // Tile Map Service (TMS)
    };
}

#endif	// INC_TILE_TYPE_H

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


