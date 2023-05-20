/**
 * @file   raster_sdl_renderer.h
 * @date   5/3/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_SDL_RENDERER_H
#define INC_RASTER_SDL_RENDERER_H

#include "common.h"
#include "map_view.h"
#include "raster_common.h"
#include "layer_renderer.h"

#include "painter/painter.h"

#include "pager/pager.h"

class SdlApplication;

struct SDL_Renderer;
struct SDL_Window;

namespace gis {

    class RasterSDLRenderer 
        : public LayerRenderer {
    public:
        virtual bool Initialize() override;
        virtual void DisplayGeometry() override;
        virtual void DisplayLabel() override;

        void SetSDLApplication(SdlApplication* sdlApplication);
        void SetMapView(std::shared_ptr<gis::MapView> mapView);
        void SetPager(std::shared_ptr<gis::Pager> pager);
        void SetRasterAssets(const GisRasterTileHashDictionary* assets);
    protected:

        /** @brief   The painter */
        basic_engine::Painter mPainter;

        /** @brief   True to enable, false to disable the information */
        bool mEnableInfo{ true };

        /** @brief   The window */
        SDL_Window* mWindow{ nullptr };

        /** @brief   The renderer */
        SDL_Renderer* mRenderer{ nullptr };

        /** @brief   The sdl application */
        SdlApplication* mSDLApplication{ nullptr };

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
#endif	// INC_RASTER_SDL_RENDERER_H

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


