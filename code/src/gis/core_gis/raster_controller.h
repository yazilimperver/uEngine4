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

#include "pager/pager.h"
#include "pager/pager_listener.h"

class SdlApplication;

namespace infra {
    class AssetService;
}

namespace gis {
    class TileNameCalculator;

    class RasterController 
        : public LayerController
        , public gis::PagerListener {
    public:
        virtual bool IsInitialized() override;
        virtual bool Initialize() override;
        virtual void Update() override;

        void SetLoaderName(std::string_view name);
        void SetTileSize(uint32_t tileSize);
        void SetSourceInfo(bool isOnline, std::string_view path, std::string_view extension);

        void SetAssetSerivce(infra::AssetService* assetService);
        void SetSDLApplication(SdlApplication* sdlApplication);
        void SetMapView(std::shared_ptr<gis::MapView> mapView);
       
        std::shared_ptr<gis::Pager> GetPager();
        const GisRasterTileHashDictionary* GetRasterTileAssets() const;

        void AssignTileIDCalculator(std::shared_ptr<gis::TileNameCalculator> tileNameCalculator);
    private:
        /** @brief   Inherited via PagerListener */
        virtual void PagedTilesUpdated() override;
      
        /** @brief   Pafta adetlerini belirleyelim */
        void DetermineTileCount();

        /** @brief   Pager'in tetikleyen fonksiyon */
        void TriggerPager();

        /** @brief   Piksel cinsidnden pafta boyutu */
        uint32_t mTileSize{ 256 };

        /** @brief   The tile per axis */
        int32_t mTilePerAxis{ 5 };
        
        /** @brief   Pafta kaynak bilgileri*/
        bool mIsOnline{ false };
        std::string mPath;
        std::string mExtension;

        /** @brief   The sdl application */
        SdlApplication* mSDLApplication{ nullptr };

        /** @brief   True if is initialized, false if not */
        bool mIsInitialized{ false };

        /** @brief   Yuklenecek paftalar */
        std::shared_ptr<gis::Pager> mPager{ nullptr };

        /** @brief   Pafta tanimlayici hesaplayicisi */
        std::shared_ptr<gis::TileNameCalculator> mTileIdCalculator{ nullptr };

        /** @brief   Katmanin genel cografik veriler icin kullanacagi harita gorunumu */
        std::shared_ptr<gis::MapView> mMapView{ nullptr };

        /** @brief   Raster katmani icin kullanilacak olan yukleyici sinifin ismi ve kotaricisidir */
        std::string mLoaderName{ "STBImageLoader" };
        AssetLoaderHandle mLoaderHandle{ -1 };

        /** @brief   Asset servisi */
        infra::AssetService* mAssetService{ nullptr };

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


