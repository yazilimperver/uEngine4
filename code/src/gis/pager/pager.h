/**
 * @file pager.h.
 * @date 2.07.2022
 * @author Yazilimperver
 * @brief Cografik paftalarin yüklenmesinden sorumlu olan siniftir. Simdilik basit bir kontrol ile paftalar belirlenecektir (TODO: ileride daha akilli pafta yukleme eklenebilir)
 * 		  Gorevler:
 *          - Thread pool ile coklu yukleme destegi  
 * 		    - Verilen konum bilgisine göre pafta hesaplama (bunu tile id calculator uzerinden yapabiliriz
 * 		    - Hangi paftalarin yuklenecegi/silinecegi  
 * 		    - Paftalarin yuklemenin tetiklenmesi  
 * 		  TODO:
 * 		    - PointInPixel'i template parametresi olarak verebiliriz
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef PAGER_H_
#define PAGER_H_

#include "concurrency\basic_thread_pool.h"

#include "pager_service.h"
#include "pager_reference.h"
#include "tile_origin.h"

namespace gis {
    class Pager 
        : public PagerService {
    public:
        virtual void UpdateReference(const PointInPixels& newCenter, uint32_t zoomLevel) override;
        void Update();

        const PointInPixels& ProvidedPosition() const;
        uint32_t ProvidedZoom() const;
        TileId ProvidedTileId() const;
        TileOrigin Origin() const;
        void SetOrigin(TileOrigin origin);

        virtual const std::vector<TileId>& ActiveTiles() override;

        std::vector<TileId> LastCalculatedTiles();
        std::vector<TileId> TilesToDispose();
        std::vector<TileId> TilesToLoad();
    private:

        /** @brief Yeni paftalari hesaplamali miyiz? */
        bool IsReferenceChanged() const;

        /** @brief Pafta tipi
                   TODO: bu kisimlar tile id calculator icine gidebilir*/
        TileOrigin mTileOrigin{ TileOrigin::Tms };

        /** @brief Paftalari yuklemek icin kullanacagimiz thread pool */
        BasicThreadPool mThreadPool;

        /** @brief Su an mevcut alan icerisinde bulunan pafta tanimlayicilari */
        std::vector<TileId> mActiveTileIdList;
        
        /** @brief Disaridan verilen en son referans bilgiler */
        PagerReference mProvidedCenter;

        /** @brief Pager icin kullanacagimiz referans konum */
        PagerReference mCenterUsed;

        /** @brief Her bir eksen icin yuklenecek pafta adeti */
        uint32_t mTilePerAxis{3};

        /** @brief En son hesaplanan pafta listesi */
        std::vector<TileId> mLastCalculatedTilesToPage;
        std::vector<TileId> mTilesToDispose;
        std::vector<TileId> mTilesToLoad;
    };
 }

 /*
struct STile;
class CTileIDCalculator;

class CPager
{
public:
    //! The constructor
    CPager();

    //! Set the number of tiles per axis 
    EStatusCode assignTilePerAxis(DUINT32 a_uNumberOfTiles);

    //! Initialize tile data
    EStatusCode initialize(DUINT8*& a_ruTileDataPoolAddress, DUINT32 a_uDataSize);

    //! Either updated, request list is full, no update is required
    //! Input is geographic coordinate
    EStatusCode update(DREAL32 a_fLongitude, DREAL32 a_fLatitude);

    //! Reset last set tile id
    void reset();

    //! Tile id calculator for corresponding pager
    void setTileIDCalculator(const CTileIDCalculator*& a_rVal);

    //! return state data
    SPagerStateData& getPagerStateData();

    //! Threshold API
    void setAbruptThreshold(DREAL32 a_fVal);
private:
    //! Determine new tile requests and currently required (new active) tiles
    void determineNewTiles();
    void determineNewTiles(const STileID& a_rCurrentTileID);

    void determineTile(DREAL32 a_fCurrentLong, DREAL32 a_fCurrentLat, STileID a_tileToRequest);

    void determineTile(STileID a_tileToRequest);

    //! Determine items to dispose from current active tiles
    void determineTilesToDispose();

    //! Dispose tiles
    void disposeActiveTiles();

    //! The tile capacity. Note this should be in the form of square (x*x)
    DUINT32 m_uTileCapacity;

    //! The tile per axis
    DUINT32 m_uTilePerAxis;

    //! Tile id calculator that will be used for this pager
    const CTileIDCalculator* m_pTileIDCalculator;

    //! The reference position for pager
    DREAL32 m_fLastLongitude;
    DREAL32 m_fLastLatitude;

    //! Last tile id that is used for request (reference position)
    STileID m_nReferenceTileId;

    //! First tile request
    DBOOL m_bIsFirstRequest;

    //! Is initialized
    DBOOL m_bIsInitialized;

    //! The paging local variables
    SPagerLocalData m_pagerLocalData;

    //! The paging state data
    SPagerStateData m_pagerStateData;

    //! The pager abrupt movement threshold in degree
    //! The pager will not perform update if movement is faster than this
    DREAL32 m_fAbruptThreshold;
};
*/

#endif // !PAGER_H_