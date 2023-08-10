/**
 * @file   raster_sdl_renderer.h
 * @date   5/3/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_GL_RENDERER_H
#define INC_RASTER_GL_RENDERER_H

#include <utility>

#include "core_gis/common.h"
#include "core_gis/map_view.h"
#include "core_gis/raster_common.h"
#include "core_gis/layer_renderer.h"

#include "gl_painter/gl_basic_painter.h"

#include "pager/pager.h"

class SdlApplication;

namespace gis {

    class RasterGLRenderer 
        : public LayerRenderer {
    public:
        virtual bool Initialize() override;
        virtual void DisplayGeometry() override;
        virtual void DisplayLabel() override;

        void SetMinMaxZoom(uint32_t minZoom, uint32_t maxZoom);
        void SetTransparency(double transparency);
        void SetTileSize(uint32_t tileSize);
        void SetSDLApplication(SdlApplication* sdlApplication);
        void SetMapView(std::shared_ptr<gis::MapView> mapView);
        void SetPager(std::shared_ptr<gis::Pager> pager);
        void SetRasterAssets(const GisRasterTileHashDictionary* assets);
        void SetDebugInfoVisibility(bool visibility);
        void SetPainter(std::shared_ptr<gl::GLBasicPainter> painter);
    protected:

        /** @brief   The painter */
        std::shared_ptr<gl::GLBasicPainter> mGLPainter;

        /** @brief   True to enable, false to disable the information */
        bool mEnableDebugInfo{ true };

        /** @brief   The sdl application */
        SdlApplication* mSDLApplication{ nullptr };

        /** @brief   Piksel cinsidnden pafta boyutu */
        uint32_t mTileSize{ 256 };

        /** @brief   Katman gosterim icin izin verilerin zoom araliklari */
        std::pair<uint32_t, uint32_t> mMinMaxZoom;

        /** @brief   Katman transparanligi */
        double mTransparency{ 1.0 };

        /** @brief   Pencerenin merkezi */
        PointInPixels mScreenCenter{ 320, 240 };

        /** @brief   True if is initialized, false if not */
        bool mIsInitialized{ false };

        /** @brief   Yuklenecek paftalar */
        std::shared_ptr<gis::Pager> mPager{ nullptr };

        /** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
        std::shared_ptr<gis::MapView> mMapView{ nullptr };

        /** @brief   Yuklenen raster pafalari */
        const GisRasterTileHashDictionary* mRasterAssets{ nullptr };
    };
}
#endif	// INC_RASTER_GL_RENDERER_H

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


