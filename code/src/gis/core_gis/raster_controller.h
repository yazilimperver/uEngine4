/**
 * @file   raster_controller.h
 * @date   5/2/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_RASTER_CONTROLLER_H
#define INC_RASTER_CONTROLLER_H


#include "map_view.h"
#include "raster_common.h"
#include "layer_controller.h"

#include "gis_asset/gis_map_asset.h"
#include "gis_asset/gis_map_loader.h"

#include "pager/pager.h"
#include "pager/pager_listener.h"
#include "pager/gtile_file_calculator.h"

class SdlApplication;

namespace gis {
    class RasterSDLRenderer;

    class RasterController 
        : public LayerController
        , public gis::PagerListener {
    public:
        virtual bool IsInitialized() override;
        virtual bool Initialize() override;
        virtual void Update() override;

        void SetSDLApplication(SdlApplication* sdlApplication);
        void SetMapView(std::shared_ptr<gis::MapView> mapView);
        void SetRasterRenderer(std::shared_ptr<RasterSDLRenderer> renderer);
       
        std::shared_ptr<gis::Pager> GetPager();
        const GisRasterTileHashDictionary* GetRasterTileAssets() const;
    private:
        /** @brief   Inherited via PagerListener */
        virtual void PagedTilesUpdated() override;
      
        /** @brief   Pafta adetlerini belirleyelim */
        void DetermineTileCount();

        /** @brief   Pager'in tetikleyen fonksiyon */
        void TriggerPager();

        /** @brief   The tile per axis */
        int32_t mTilePerAxis{ 5 };

        /** @brief   The sdl application */
        SdlApplication* mSDLApplication{ nullptr };

        /** @brief   True if is initialized, false if not */
        bool mIsInitialized{ false };

        /** @brief   The raster renderer */
        std::shared_ptr<RasterSDLRenderer> mRasterRenderer{ nullptr };

        /** @brief   Yuklenecek paftalar */
        std::shared_ptr<gis::Pager> mPager{ nullptr };

        /** @brief   Pafta tanimlayici hesaplayicisi */
        std::shared_ptr<gis::GTileFileCalculator> mTileIdCalculator{ nullptr };

        /** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
        std::shared_ptr<gis::MapView> mMapView{ nullptr };

        /** @brief   Raster pafta yukleme */
        gis_asset::GisMapLoader mMapLoader;

        /** @brief   Yuklenen paftalarin tutulacagi liste */
        GisRasterTileHashDictionary mRasterAssets;
    };
}

#endif	// INC_RASTER_CONTROLLER_H

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


