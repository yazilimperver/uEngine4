#include "pager.h"

#include "core_gis/tile_tms.h"

#include "pager/pager_listener.h"

namespace gis {
    void Pager::UpdateReference(const PointInPixels& newCenter, uint32_t zoomLevel) {
        mProvidedCenter.Position = newCenter;
        mProvidedCenter.ZoomLevel = zoomLevel;

        if (TileOrigin::Tmz == mTileOrigin){
            auto calculatedTileInfo = TileTms::PixelToTile(newCenter, zoomLevel);

            mProvidedCenter.TileInfo.TileX = calculatedTileInfo.TmsX();
            mProvidedCenter.TileInfo.TileY = calculatedTileInfo.TmsY();
            mProvidedCenter.TileInfo.ZoomLevel = zoomLevel;
        }
        else {
            auto calculatedTileInfo = TileTms::PixelToTile(newCenter, zoomLevel).ObtainGoogleTileInfo();
            
            mProvidedCenter.TileInfo.TileX = calculatedTileInfo.x;
            mProvidedCenter.TileInfo.TileY = calculatedTileInfo.y;
            mProvidedCenter.TileInfo.ZoomLevel = zoomLevel;
        }
    }
    
    void Pager::Update() {
        if (IsReferenceChanged()){
            mCenterUsed = mProvidedCenter;

            auto prevCalculatedTiles = mLastCalculatedTilesToPage;

            mLastCalculatedTilesToPage.clear();

            TileId tileToLoad;
            int32_t radius = mTilePerAxis / 2;
            
            tileToLoad.ZoomLevel = mCenterUsed.ZoomLevel;
            tileToLoad.TileY = mCenterUsed.TileInfo.TileY - radius;

            for (uint32_t i = 0; i < mTilePerAxis; i++) {
                tileToLoad.TileX = mCenterUsed.TileInfo.TileX - radius;

                for (uint32_t j = 0; j < mTilePerAxis; j++) {
                    mLastCalculatedTilesToPage.push_back(tileToLoad);
                    tileToLoad.TileX++;
                }

                tileToLoad.TileY++;
            }

            // Fark algoritmalarinin kosabilmesi icin once siralama yapalim
            std::sort(mLastCalculatedTilesToPage.begin(), mLastCalculatedTilesToPage.end());
            std::sort(prevCalculatedTiles.begin(), prevCalculatedTiles.end());

            // Once  artik ihtiyac olmayan paftalari buluyoruz
            mTilesToLoad.clear();
            std::set_difference(mLastCalculatedTilesToPage.begin(), mLastCalculatedTilesToPage.end(), 
                prevCalculatedTiles.begin(), prevCalculatedTiles.end(),
                std::inserter(mTilesToLoad, mTilesToLoad.begin()));

            // Simdi de yuklenecek olanlari bulalim 
            mTilesToDispose.clear();
            std::set_difference(prevCalculatedTiles.begin(), prevCalculatedTiles.end(),
                mLastCalculatedTilesToPage.begin(), mLastCalculatedTilesToPage.end(),
                std::inserter(mTilesToDispose, mTilesToDispose.begin()));

            if (nullptr != mPagerListener
                &&
                mTilesToLoad.size() > 0) {
                mPagerListener->PagedTilesUpdated();
            }
        }
    }

    const PointInPixels& Pager::ProvidedPosition() const {
        return mProvidedCenter.Position;
    }

    uint32_t Pager::ProvidedZoom() const {
        return mProvidedCenter.ZoomLevel;
    }

    TileId Pager::ProvidedTileId() const {
        return mProvidedCenter.TileInfo;
    }

    TileOrigin Pager::Origin() const {
        return mTileOrigin;
    }

    void Pager::SetOrigin(TileOrigin origin) {
        mTileOrigin = origin;
    }

    const std::vector<TileId>& Pager::ActiveTiles() const {
        return mLastCalculatedTilesToPage;
    }

    const std::vector<TileId>& Pager::TilesToDispose() const {
        return mTilesToDispose;
    }

    const std::vector<TileId>& Pager::TilesToLoad() const {
        return mTilesToLoad;
    }
    
    bool Pager::IsReferenceChanged() const {
        return mProvidedCenter != mCenterUsed;
    }
    
    void Pager::AssignListener(PagerListener* listener) {
        mPagerListener = listener;
    }
    void Pager::SetTilePerAxis(uint32_t tilePerAxis) {
        mTilePerAxis = tilePerAxis;
    }
    
    uint32_t Pager::TilePerAxis() const {
        return mTilePerAxis;
    }
}