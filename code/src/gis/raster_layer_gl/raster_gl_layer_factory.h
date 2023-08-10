/**
 * @file   raster_gl_layer_factory.h
 * @date   7/2/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_GL_LAYER_FACTORY_H
#define INC_RASTER_GL_LAYER_FACTORY_H

#include "core_gis/layer_factory.h"

namespace infra {
    class AssetService;
}

namespace gl {
    class GLBasicPainter;
}

namespace gis {
    class RasterGLLayerFactory
        : public LayerFactory {
    public:
        const static std::string LayerTypeName;
        virtual std::string LayerType() const override;

        /** @brief Verilen metadata kullanilarak katmani olusturur */
        virtual std::shared_ptr<Layer> CreateLayer(const ParameterSet layerMetadata) override;
        virtual void SetSDLApplication(SdlApplication* sdlApplication) override;
        virtual void SetMapView(std::shared_ptr<gis::MapView> mapView) override;
        void SetPainter(std::shared_ptr<gl::GLBasicPainter> painter);

    private:
        /** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
        std::shared_ptr<gis::MapView> mMapView{ nullptr };

        /** @brief   SDL uygulama isaretcisi */
        SdlApplication* mSDLApplication{ nullptr };

        /** @brief  Yuklenecek veriler icin kullanilabilecek servis */
        infra::AssetService* mAssetService{ nullptr };

        /** @brief   Gorsellestirme icin kullanilabilecek olan painter */
        std::shared_ptr<gl::GLBasicPainter> mPainter{ nullptr };
    };
}

#endif	// INC_RASTER_GL_LAYER_FACTORY_H

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


