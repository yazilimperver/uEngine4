/**
 * @file   layer_service.h
 * @date   5/1/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_SERVICE_H
#define INC_LAYER_SERVICE_H

#include <cstdint>
#include <string>
#include <optional>
#include <string_view>

#include "layer_factory.h"

namespace gis {
	enum class LayerStatus;
	class Layer;

    class LayerService {
		//! Add a geographic layer
		virtual void AddLayer(std::shared_ptr<Layer> layer) = 0;
		virtual void CreateLayer(std::string_view layerName, std::string_view layerType) = 0;
		virtual void RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) = 0;

		//! Get layer
		virtual std::optional<std::shared_ptr<Layer>> GetLayer(const std::string& layerName) = 0;
		virtual std::optional<std::shared_ptr<Layer>> GetLayer(int32_t layerHandle) = 0;

		virtual std::optional<LayerStatus> GetLayerStatus(int32_t layerHandle) = 0;
		virtual std::optional<LayerStatus> GetLayerStatus(const std::string& layerName) = 0;
		virtual std::optional<int32_t> GetLayerHandle(const std::string& layerName) = 0;
		virtual void SetLayerStatus(const std::string& layerName, LayerStatus layerStatus) = 0;
		virtual void SetLayerStatus(int32_t layerHandle, LayerStatus layerStatus) = 0;
    };
}

#endif	// INC_LAYER_SERVICE_H

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


