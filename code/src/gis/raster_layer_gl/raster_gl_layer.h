/**
 * @file   raster_gl_layer.h
 * @date   5/3/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_LAYER_H
#define INC_RASTER_LAYER_H

#include <memory>

#include "core_gis/layer.h"
#include "core_gis/map_view.h"

namespace gis {
    class RasterController;
    class RasterGLRenderer;

    class RasterGLLayer
        : public Layer {
    public:
        RasterGLLayer(std::shared_ptr<RasterController> controller, std::shared_ptr<RasterGLRenderer> renderer);
        
        virtual bool Initialize() override;
        virtual std::shared_ptr<LayerRenderer> Get2DRenderer() override;
        virtual std::shared_ptr<LayerController> Get2DController() override;
        virtual LayerType GetLayerType() override;
        virtual bool HasLayerLabelDisplay() const override;
    protected:
        
        std::shared_ptr<RasterController> mRasterController{ nullptr };
        std::shared_ptr<RasterGLRenderer> mRasterRenderer{ nullptr };
    };
}

#endif	// INC_RASTER_LAYER_H

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


