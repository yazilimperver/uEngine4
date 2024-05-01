/**
 * @file   layer_configuration.h
 * @date   5/20/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_CONFIGURATION_H
#define INC_LAYER_CONFIGURATION_H

#include <vector>
#include "raster_layer_metadata.h"
#include "vector_layer_metadata.h"
#include "custom_layer_metadata.h"

namespace gis {
    struct LayerConfiguration {
        std::vector<gis::RasterLayerMetadata> RasterLayers;
        std::vector<gis::VectorLayerMetadata> VectorLayers;
        std::vector<gis::CustomLayerMetadata> CustomLayers;
    };
}

#endif	// INC_LAYER_CONFIGURATION_H

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


