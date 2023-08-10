/**
 * @file   raster_metadata.h
 * @date   5/20/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_METADATA_H
#define INC_RASTER_METADATA_H

#include <cstdint>
#include <string>

#include "tile_type.h"

namespace gis {
    //! Represent SDL parameters
    struct RasterLayerMetadata {
        std::string LayerFactory;
        TileType TileType{ TileType::XYZ };
        bool IsOnline{false};
        bool InitialVisibility{ true };
        bool UseGLRenderer{ true }; // false ise SDL kullanilacak
        uint32_t TileSize;
        uint32_t MinZoomLevel;
        uint32_t MaxZoomLevel;
        uint32_t Priority;      // 0 en ustte gorunsun
        double Transparency;    // 0 transparan, 1 tam opak
        std::string Path;
        std::string Name;
        std::string Extension;
    };
}
#endif	// INC_RASTER_METADATA_H

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


