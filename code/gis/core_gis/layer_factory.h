/**
 * @file   layer_factory.h
 * @date   5/4/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_LAYER_FACTORY_H
#define INC_LAYER_FACTORY_H

#include <memory>
#include <string_view>

class SdlApplication;
class ParameterSet;
class TileNameCalculator;

namespace gis {
    class LayerService;
    class LayerIterator;
    class TileNameFactory;
    class MapView; 
    class Layer;
    class LayerFactory {
    public:
        virtual ~LayerFactory() = default;
        virtual std::string LayerType() const = 0;
        virtual std::shared_ptr<Layer> CreateLayer(const ParameterSet layerParameters) = 0;
        virtual void SetLayerIterator(LayerIterator* iterator) = 0;
        virtual void SetLayerService(LayerService* service) = 0;
        virtual void SetSDLApplication(SdlApplication* sdlApplication) = 0;
        virtual void SetMapView(std::shared_ptr<gis::MapView> mapView) = 0;
        virtual void RegisterTileNameFactory(std::string_view layerType, std::shared_ptr<TileNameFactory> factory) = 0;
    };
}
#endif	// INC_LAYER_FACTORY_H

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


