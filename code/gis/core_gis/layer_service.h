/**
 * @file   layer_service.h
 * @date   5/1/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef LAYER_SERVICE
#define LAYER_SERVICE

#include <cstdint>
#include <string>
#include <optional>
#include <string_view>
#include <functional>

#include "layer_factory.h"

class ParameterSet;

namespace gis {
	enum class LayerStatus;
	class Layer;

    class LayerService {
	public:
        /** @brief   Temel tipler */
        using SharedLayer = std::shared_ptr<Layer>;
        using LayerIteratorType = std::vector<SharedLayer>::iterator;

        virtual void MoveUp(int layerIndexToMove) = 0;
        virtual void MoveDown(int layerIndexToMove) = 0;

		//! Add a geographic layer
		virtual void AddLayer(SharedLayer layer, uint32_t priority) = 0;
		virtual void CreateLayer(std::string_view factoryName, ParameterSet layerMetadata) = 0;
		virtual void RegisterLayerFactory(std::unique_ptr<LayerFactory> layerFactory) = 0;

        //! Katman tiplerine gore butun cizimlar oncesi ve sonrasi yapilacaklar icin ilgili metotlarin gecirelim
        virtual void SetPreUIDisplayHook(std::function<void(bool)> hookFunc) = 0;
        virtual void SetPostUIDisplayHook(std::function<void(bool)> hookFunc) = 0;

		//! Get layer
		virtual std::optional<std::shared_ptr<gis::Layer>> GetLayer(std::string_view layerName) = 0;

		virtual std::optional<gis::LayerStatus> Status(std::string_view layerName) = 0;
		virtual void SetStatus(std::string_view layerName, LayerStatus layerStatus) = 0;
    };
}

#endif /* LAYER_SERVICE */

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


