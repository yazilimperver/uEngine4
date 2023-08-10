/**
 * @file   layer_configurator_serializer.h
 * @date   5/20/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_CONFIGURATOR_SERIALIZER_H
#define INC_LAYER_CONFIGURATOR_SERIALIZER_H

#include "raster_layer_metadata.h"
#include "layer_configuration.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

namespace gis {
	template<class Archive>
	void serialize(Archive& archive, gis::RasterLayerMetadata& m) {

		auto tileType = static_cast<int32_t>(m.TileType);

		archive(cereal::make_nvp("LayerFactory", m.LayerFactory), 
			cereal::make_nvp("TileType", tileType),
			cereal::make_nvp("IsOnline", m.IsOnline),
			cereal::make_nvp("InitialVisibility", m.InitialVisibility),
            cereal::make_nvp("TileSize", m.TileSize),
			cereal::make_nvp("UseGLRenderer", m.UseGLRenderer),
			cereal::make_nvp("MinZoomLevel", m.MinZoomLevel),
			cereal::make_nvp("MaxZoomLevel", m.MaxZoomLevel),
			cereal::make_nvp("Priority", m.Priority),
			cereal::make_nvp("Transparency", m.Transparency),
			cereal::make_nvp("Path", m.Path),
			cereal::make_nvp("Name", m.Name),
			cereal::make_nvp("Extension", m.Extension));

		m.TileType = static_cast<gis::TileType>(tileType);
	}

	template<class Archive>
	void serialize(Archive& archive, gis::LayerConfiguration& m) {
		archive(cereal::make_nvp("RasterLayers", m.RasterLayers));
	}
}

#endif	// INC_LAYER_CONFIGURATOR_SERIALIZER_H

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


