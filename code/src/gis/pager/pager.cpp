#include "pager.h"

#include "core_gis/tile_tms.h"

namespace gis {
    void Pager::UpdateReference(const PointInPixels& newCenter, uint32_t zoomLevel) {
        mProvidedCenter.Position = newCenter;
        mProvidedCenter.ZoomLevel = zoomLevel;

        if (TileOrigin::Tms == mTileOrigin){
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
    
    const std::vector<TileId>& Pager::ActiveTiles()    {
        return std::vector<TileId>();
    }

    std::vector<TileId> Pager::LastCalculatedTiles() {
        return mLastCalculatedTilesToPage;
    }

    std::vector<TileId> Pager::TilesToDispose() {
        return mTilesToDispose;
    }

    std::vector<TileId> Pager::TilesToLoad() {
        return mTilesToLoad;
    }
    
    bool Pager::IsReferenceChanged() const {
        return mProvidedCenter != mCenterUsed;
    }
}

/*
#include <Pager/CPager.h>
#include <Pager/STile.h>
#include <Pager/CTileIDCalculator.h>

#include <Logger/LoggerDefinitions.h>

#include <String/CString128.h>

#include <math.h>
#include <stdlib.h>

namespace SHInfraStruct
{
    CPager::CPager()
        : m_uTileCapacity(0U),
        m_uTilePerAxis(0U),
        m_pTileIDCalculator(0),
        m_fLastLongitude(0.0F),
        m_fLastLatitude(0.0F),
        m_nReferenceTileId(-1, -1),
        m_bIsFirstRequest(true),
        m_bIsInitialized(false),
        m_fAbruptThreshold(0.5F)
    {
        m_pagerLocalData.m_uCurrentTileCount = 0U;
        m_pagerLocalData.m_uNewlyRequiredTileCount = 0U;
        m_pagerLocalData.m_uTilesToDisposeCount = 0U;
        m_pagerLocalData.m_uNewActiveTileCount = 0U;

        memset(&m_pagerLocalData.m_aCurrentTiles[0], 0, sizeof(STileID) * G_PAGER_MAX_TILE_CAPACITY);
        memset(&m_pagerLocalData.m_aNewlyRequiredTiles[0], 0, sizeof(STileID) * G_PAGER_MAX_TILE_CAPACITY);
        memset(&m_pagerLocalData.m_anTilesToDispose[0], 0, sizeof(DINT32) * G_PAGER_MAX_TILE_CAPACITY);
        memset(&m_pagerLocalData.m_anNewActiveTiles[0], 0, sizeof(DINT32) * G_PAGER_MAX_TILE_CAPACITY);
    }

    EStatusCode CPager::assignTilePerAxis(DUINT32 a_uNumberOfTiles)
    {
        EStatusCode status = eSC_FAILURE;

        if ((a_uNumberOfTiles * a_uNumberOfTiles) <= G_PAGER_MAX_TILE_CAPACITY)
        {
            m_uTilePerAxis = a_uNumberOfTiles;
            m_uTileCapacity = a_uNumberOfTiles * a_uNumberOfTiles;
            status = eSC_SUCCESS;
        }

        return status;
    }

    EStatusCode CPager::initialize(DUINT8*& a_ruTileDataPoolAddress, DUINT32 a_uDataSize)
    {
        EStatusCode nStatus = eSC_FAILURE;
        CString128 log;
        DUINT32 uI = 0U;

        if ((0 != a_ruTileDataPoolAddress)
            &&
            (0U != m_uTileCapacity))
        {
            if ((m_uTileCapacity % 2U) == 0U)
            {
                logError("[CPager::initialize] The pool size is not perfect or odd!");
            }
            else
            {
                log = CString128("[CPager::initialize] Tile per axis: %%. The pager total tile capacity is %%.");
                logInfo(log.marker(m_uTilePerAxis).marker(m_uTileCapacity));

                // Initialize page state data
                if ((m_uTileCapacity <= G_PAGER_MAX_TILE_CAPACITY)
                    &&
                    (0 != m_pTileIDCalculator)
                    &&
                    (a_uDataSize >= (m_uTileCapacity * sizeof(SHInfraStruct::STile))))
                {
                    // Obtain tile info from pool
                    for (uI = 0U; uI < m_uTileCapacity; ++uI)
                    {
                        // Reserve tile
                        m_pagerStateData.m_pReservedTiles[uI]
                            = reinterpret_cast<STile*>(a_ruTileDataPoolAddress + (sizeof(STile) * uI));

                        m_pagerStateData.m_pReservedTiles[uI]->m_uTileHandle = uI;

                        m_pagerStateData.m_uReservedTileCount++;

                        // Put it to available tile
                        m_pagerStateData.m_pAvailableTileIds[uI] = static_cast<DINT32>(uI);
                        m_pagerStateData.m_uAvailableTileCount++;
                    }

                    nStatus = eSC_SUCCESS;
                }
                else
                {
                    logError("[CPager::initialize] Error in pager initialization!");
                }
            }
        }

        if (eSC_SUCCESS == nStatus)
        {
            m_bIsInitialized = true;
        }

        return nStatus;
    }

    EStatusCode CPager::update(DREAL32 a_fLongitude, DREAL32 a_fLatitude)
    {
        EStatusCode nStatus = eSC_FAILURE;
        STileID currentTileID;

        //! Is abrupt movement change is occurred
        DBOOL bAbruptMovement = false;

        if (true == m_bIsInitialized)
        {
            // no slot available for new requests wait for it
            if ((m_pagerStateData.m_uRequestedTileCount + m_pagerStateData.m_uTilesToRequestCount) >= m_uTileCapacity)
            {
                nStatus = eSC_LIST_FULL;
            }
            else
            {
                if ((abs(a_fLongitude - m_fLastLongitude) > m_fAbruptThreshold)
                    ||
                    (abs(a_fLatitude - m_fLastLatitude) > m_fAbruptThreshold))
                {
                    bAbruptMovement = true;

                    logInfo("[CPagerV2::update] Abrupt movement! No update");
                }

                m_fLastLongitude = a_fLongitude;
                m_fLastLatitude = a_fLatitude;

                if (false == bAbruptMovement)
                {
                    // Reset local data
                    m_pagerLocalData.m_uCurrentTileCount = 0U;
                    m_pagerLocalData.m_uNewlyRequiredTileCount = 0U;
                    m_pagerLocalData.m_uTilesToDisposeCount = 0U;
                    m_pagerLocalData.m_uNewActiveTileCount = 0U;

                    // Check current tile
                    m_pTileIDCalculator->readTileID(m_fLastLongitude, m_fLastLatitude, currentTileID);

                    if (((true == m_bIsFirstRequest)
                        &&
                        (true == m_pTileIDCalculator->checkIfInRange(m_fLastLongitude, m_fLastLatitude)))
                        ||
                        ((true == m_pTileIDCalculator->checkIfInRange(m_fLastLongitude, m_fLastLatitude))
                            &&
                            (currentTileID != m_nReferenceTileId)))
                    {
                        m_bIsFirstRequest = false;

                        // Determine new tiles
                        if (0 == m_pTileIDCalculator->getZoomScaleLevel())
                        {
                            this->determineNewTiles();
                        }
                        else
                        {
                            // Will be removed later! Exist for XYZ tile id calculator
                            this->determineNewTiles(currentTileID);
                        }

                        // Determine tile to dispose
                        this->determineTilesToDispose();

                        // If we do not have any free slot for requests then ignore new requests and wait for free slots
                        if ((m_pagerStateData.m_uRequestedTileCount + m_pagerLocalData.m_uNewlyRequiredTileCount)
                            <= (m_pagerStateData.m_uAvailableTileCount + m_pagerLocalData.m_uTilesToDisposeCount))
                        {
                            // Update tile id
                            m_nReferenceTileId = currentTileID;

                            // Dispose active tiles
                            this->disposeActiveTiles();

                            // Paging state data is updated
                            nStatus = eSC_SUCCESS;
                        }
                        else
                        {
                            nStatus = eSC_LIST_FULL;
                            // Wait for load
                        }
                    }
                }
            }
        }

        return nStatus;
    }

    void CPager::reset()
    {
        DUINT32 uI = 0U;
        m_nReferenceTileId.m_nTileX = -1;
        m_nReferenceTileId.m_nTileY = -1;

        // reset all raster tile data statuses
        m_pagerStateData.m_uActiveTileCount = 0U;
        m_pagerStateData.m_uRequestedTileCount = 0U;
        m_pagerStateData.m_uTilesToRequestCount = 0U;
        m_pagerStateData.m_uAvailableTileCount = 0U;

        // Prepare available tile pool
        for (uI = 0U; uI < m_pagerStateData.m_uReservedTileCount; ++uI)
        {
            m_pagerStateData.m_pAvailableTileIds[uI]
                = static_cast<DINT32>(m_pagerStateData.m_uReservedTileCount - uI - 1U);
        }

        m_pagerStateData.m_uAvailableTileCount = m_pagerStateData.m_uReservedTileCount;
    }

    void CPager::setTileIDCalculator(const CTileIDCalculator*& a_rVal)
    {
        m_pTileIDCalculator = a_rVal;
    }

    SPagerStateData& CPager::getPagerStateData()
    {
        return m_pagerStateData;
    }

    void CPager::setAbruptThreshold(DREAL32 a_fVal)
    {
        m_fAbruptThreshold = a_fVal;
    }

    void CPager::determineNewTiles(const STileID& a_rCurrentTileID)
    {
        STileID tileToRequest;
        DINT32 nTmpTileAxis = 0;
        DINT32 nDeltaX = 0;
        DINT32 nDeltaY = 0;

        determineTile(a_rCurrentTileID);

        if (m_uTilePerAxis > 1U)
        {
            nTmpTileAxis = G_TILE_AXIS_DEFAULT_VALUE;
            nDeltaX = a_rCurrentTileID.m_nTileX - m_nReferenceTileId.m_nTileX;
            nDeltaY = a_rCurrentTileID.m_nTileY - m_nReferenceTileId.m_nTileY;
            tileToRequest = a_rCurrentTileID;

            if ((static_cast<DUINT32>(abs(nDeltaX)) > m_uTilePerAxis
                || static_cast<DUINT32>(abs(nDeltaY)) > m_uTilePerAxis)
                || ((nDeltaX == 0 && nDeltaY < 0) || (nDeltaX > 0) && (nDeltaY < 0)))
            {
                while (m_uTilePerAxis >= static_cast<DUINT32>(nTmpTileAxis))
                {
                    tileToRequest.m_nTileY = a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2);
                    tileToRequest.m_nTileX = a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2);

                    while (tileToRequest.m_nTileX <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileX) - 1))
                    {
                        determineTile(tileToRequest);
                        tileToRequest.m_nTileX++;
                    }

                    while (tileToRequest.m_nTileY <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileY) - 1))
                    {
                        determineTile(tileToRequest);
                        tileToRequest.m_nTileY++;
                    }

                    while (((a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileX)
                    {
                        determineTile(tileToRequest);
                        tileToRequest.m_nTileX--;
                    }

                    while (((a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileY)
                    {
                        determineTile(tileToRequest);
                        tileToRequest.m_nTileY--;
                    }

                    nTmpTileAxis = nTmpTileAxis + 2;
                }
            }
            else
            {
                if (((nDeltaX > 0) && (nDeltaY > 0)) || ((nDeltaX > 0) && (nDeltaY == 0)))
                {
                    while (m_uTilePerAxis >= static_cast<DUINT32>(nTmpTileAxis))
                    {
                        tileToRequest.m_nTileY = a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2);
                        tileToRequest.m_nTileX = a_rCurrentTileID.m_nTileX + (nTmpTileAxis / 2);

                        while (tileToRequest.m_nTileY <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileY) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY++;
                        }

                        while (((a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileX)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX--;
                        }

                        while (((a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileY)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY--;
                        }

                        while (tileToRequest.m_nTileX <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileX) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX++;
                        }

                        nTmpTileAxis = nTmpTileAxis + 2;
                    }
                }
                else if (((nDeltaX < 0) && (nDeltaY > 0)) || ((nDeltaX == 0) && (nDeltaY > 0)))
                {
                    while (m_uTilePerAxis >= static_cast<DUINT32>(nTmpTileAxis))
                    {
                        tileToRequest.m_nTileY = a_rCurrentTileID.m_nTileY + (nTmpTileAxis / 2);
                        tileToRequest.m_nTileX = a_rCurrentTileID.m_nTileX + (nTmpTileAxis / 2);

                        while (((a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileX)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX--;
                        }

                        while (((a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileY)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY--;
                        }

                        while (tileToRequest.m_nTileX <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileX) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX++;
                        }

                        while (tileToRequest.m_nTileY <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileY) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY++;
                        }

                        nTmpTileAxis = nTmpTileAxis + 2;
                    }
                }
                else if (((nDeltaX < 0) && (nDeltaY == 0)) || ((nDeltaX < 0) && (nDeltaY < 0)))
                {
                    while (m_uTilePerAxis >= static_cast<DUINT32>(nTmpTileAxis))
                    {
                        tileToRequest.m_nTileY = a_rCurrentTileID.m_nTileY + (nTmpTileAxis / 2);
                        tileToRequest.m_nTileX = a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2);

                        while (((a_rCurrentTileID.m_nTileY - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileY)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY--;
                        }

                        while (tileToRequest.m_nTileX <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileX) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX++;
                        }

                        while (tileToRequest.m_nTileY <= (((nTmpTileAxis / 2) + a_rCurrentTileID.m_nTileY) - 1))
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileY++;
                        }

                        while (((a_rCurrentTileID.m_nTileX - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileX)
                        {
                            determineTile(tileToRequest);
                            tileToRequest.m_nTileX--;
                        }
                        nTmpTileAxis = nTmpTileAxis + 2;
                    }
                }
            }
        }
    }

    void CPager::determineNewTiles()
    {
        DREAL32 fTileWidth = m_pTileIDCalculator->readTileWidth(m_fLastLatitude);
        DREAL32 fTileHeight = m_pTileIDCalculator->readTileHeight();
        DREAL32 fLeftPosition = m_fLastLongitude;
        DREAL32 fTopPosition = m_fLastLatitude;
        DREAL32 fCurrentLong = m_fLastLongitude;
        DREAL32 fCurrentLat = m_fLastLatitude;
        STileID centerTileToRequest;
        STileID tileToRequest;
        DINT32 nTmpTileAxis = 0;

        m_pTileIDCalculator->readTileID(fCurrentLong, fCurrentLat, centerTileToRequest);
        determineTile(fCurrentLong, fCurrentLat, centerTileToRequest);

        if (m_uTilePerAxis > 1U)
        {
            nTmpTileAxis = G_TILE_AXIS_DEFAULT_VALUE;

            while (m_uTilePerAxis >= static_cast<DUINT32>(nTmpTileAxis))
            {
                tileToRequest.m_nTileY = centerTileToRequest.m_nTileY - (nTmpTileAxis / 2);
                tileToRequest.m_nTileX = centerTileToRequest.m_nTileX - (nTmpTileAxis / 2);
                fCurrentLong = fLeftPosition - (fTileWidth * static_cast<DREAL32>((nTmpTileAxis / 2)));
                fCurrentLat = fTopPosition + (fTileHeight * static_cast<DREAL32>((nTmpTileAxis / 2)));

                while (tileToRequest.m_nTileX <= (((nTmpTileAxis / 2) + centerTileToRequest.m_nTileX) - 1))
                {
                    determineTile(fCurrentLong, fCurrentLat, tileToRequest);
                    tileToRequest.m_nTileX++;
                    fCurrentLong += fTileWidth;
                }

                while (tileToRequest.m_nTileY <= (((nTmpTileAxis / 2) + centerTileToRequest.m_nTileY) - 1))
                {
                    determineTile(fCurrentLong, fCurrentLat, tileToRequest);
                    tileToRequest.m_nTileY++;
                    fCurrentLat -= fTileHeight;
                }

                while (((centerTileToRequest.m_nTileX - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileX)
                {
                    determineTile(fCurrentLong, fCurrentLat, tileToRequest);
                    tileToRequest.m_nTileX--;
                    fCurrentLong -= fTileWidth;
                }

                while (((centerTileToRequest.m_nTileY - (nTmpTileAxis / 2)) + 1) <= tileToRequest.m_nTileY)
                {
                    determineTile(fCurrentLong, fCurrentLat, tileToRequest);
                    tileToRequest.m_nTileY--;
                    fCurrentLat += fTileHeight;
                }

                nTmpTileAxis = nTmpTileAxis + 2;
            }
        }
    }

    void CPager::determineTile(DREAL32 a_fCurrentLong, DREAL32 a_fCurrentLat, STileID a_tileToRequest)
    {
        DBOOL bTileNotExist = true;
        DUINT32 uK = 0U;

        // Calculate current tile 
        m_pTileIDCalculator->readTileID(a_fCurrentLong, a_fCurrentLat, a_tileToRequest);

        if ((a_tileToRequest.m_nTileX >= 0)
            &&
            (a_tileToRequest.m_nTileY >= 0))
        {
            m_pagerLocalData.m_aCurrentTiles[m_pagerLocalData.m_uCurrentTileCount] = a_tileToRequest;
            bTileNotExist = true;

            // First check active tiles if it is already active
            for (uK = 0U; (uK < m_pagerStateData.m_uActiveTileCount) && (true == bTileNotExist); ++uK)
            {
                if (m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pActiveTiles[uK]]->m_nTileID == a_tileToRequest)
                {
                    bTileNotExist = false;
                }
            }

            // Then check requested tiles
            if (true == bTileNotExist)
            {
                for (uK = 0U; (uK < m_pagerStateData.m_uRequestedTileCount) && (true == bTileNotExist); ++uK)
                {
                    if (m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pRequestedTiles[uK]]->m_nTileID
                        == a_tileToRequest)
                    {
                        bTileNotExist = false;
                    }
                }
            }

            // This is a new tile
            if (true == bTileNotExist)
            {
                m_pagerLocalData.m_aNewlyRequiredTiles[m_pagerLocalData.m_uNewlyRequiredTileCount] = a_tileToRequest;
                m_pagerLocalData.m_uNewlyRequiredTileCount++;

                //! FTODO: Remove later
                if (m_pagerLocalData.m_uNewlyRequiredTileCount > G_PAGER_MAX_TILE_CAPACITY)
                {
                    logError("[CPager::determineNewTiles] Error: m_uNewlyRequiredTileCount is overflown!");
                }
            }

            m_pagerLocalData.m_uCurrentTileCount++;
        }
    }

    void CPager::determineTile(STileID a_tileToRequest)
    {
        DBOOL bTileNotExist = true;
        DUINT32 uK = 0U;

        // Calculate current tile 
        if ((a_tileToRequest.m_nTileX >= 0)
            &&
            (a_tileToRequest.m_nTileY >= 0))
        {
            m_pagerLocalData.m_aCurrentTiles[m_pagerLocalData.m_uCurrentTileCount] = a_tileToRequest;
            bTileNotExist = true;

            // First check active tiles if it is already active
            for (uK = 0U; (uK < m_pagerStateData.m_uActiveTileCount) && (true == bTileNotExist); ++uK)
            {
                if (m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pActiveTiles[uK]]->m_nTileID == a_tileToRequest)
                {
                    bTileNotExist = false;
                }
            }

            // Then check requested tiles
            if (true == bTileNotExist)
            {
                for (uK = 0U; (uK < m_pagerStateData.m_uRequestedTileCount) && (true == bTileNotExist); ++uK)
                {
                    if (m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pRequestedTiles[uK]]->m_nTileID
                        == a_tileToRequest)
                    {
                        bTileNotExist = false;
                    }
                }
            }

            // This is a new tile
            if (true == bTileNotExist)
            {
                m_pagerLocalData.m_aNewlyRequiredTiles[m_pagerLocalData.m_uNewlyRequiredTileCount] = a_tileToRequest;
                m_pagerLocalData.m_uNewlyRequiredTileCount++;

                //! FTODO: Remove later
                if (m_pagerLocalData.m_uNewlyRequiredTileCount > G_PAGER_MAX_TILE_CAPACITY)
                {
                    logError("[CPager::determineNewTiles] Error: m_uNewlyRequiredTileCount is overflown!");
                }
            }

            m_pagerLocalData.m_uCurrentTileCount++;
        }
    }

    void CPager::determineTilesToDispose()
    {
        DUINT32 uJ = 0U;
        DUINT32 uI = 0U;
        // check against current tiles and find target tiles if partial load required
        DBOOL bSkipToNextItem = false;

        for (uI = 0U; uI < m_pagerStateData.m_uActiveTileCount; ++uI)
        {
            bSkipToNextItem = false;

            // Compare current active tiles against current tiles
            for (uJ = 0U; (uJ < m_pagerLocalData.m_uCurrentTileCount) && (false == bSkipToNextItem); ++uJ)
            {
                if (m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pActiveTiles[uI]]->m_nTileID
                    == m_pagerLocalData.m_aCurrentTiles[uJ])
                {
                    bSkipToNextItem = true;
                }
            }

            if (false == bSkipToNextItem)
            {
                m_pagerLocalData.m_anTilesToDispose[m_pagerLocalData.m_uTilesToDisposeCount]
                    = m_pagerStateData.m_pActiveTiles[uI];

                m_pagerLocalData.m_uTilesToDisposeCount++;
            }
            else
            {
                m_pagerLocalData.m_anNewActiveTiles[m_pagerLocalData.m_uNewActiveTileCount]
                    = m_pagerStateData.m_pActiveTiles[uI];

                m_pagerLocalData.m_uNewActiveTileCount++;
            }
        }
    }

    void CPager::disposeActiveTiles()
    {
        DINT32 nAvailableTileHndl = -1;
        DBOOL bAlreadyRequested = false;
        DUINT32 uJ = 0U;
        DUINT32 uI = 0U;

        // Set disposed tiles
        m_pagerStateData.m_uLastDisposedTileCount = 0U;
        for (uI = 0U; uI < m_pagerLocalData.m_uTilesToDisposeCount; ++uI)
        {
            // Put this item to disposed list
            m_pagerStateData.m_anLastDisposedTiles[m_pagerStateData.m_uLastDisposedTileCount]
                = m_pagerStateData.m_pReservedTiles[m_pagerLocalData.m_anTilesToDispose[uI]];

            m_pagerStateData.m_uLastDisposedTileCount++;

            // Put this item to available tile list
            m_pagerStateData.m_pAvailableTileIds[m_pagerStateData.m_uAvailableTileCount]
                = m_pagerLocalData.m_anTilesToDispose[uI];

            m_pagerStateData.m_uAvailableTileCount++;
        }

        // Set new active tiles
        m_pagerStateData.m_uActiveTileCount = m_pagerLocalData.m_uNewActiveTileCount;
        memcpy(m_pagerStateData.m_pActiveTiles,
            m_pagerLocalData.m_anNewActiveTiles,
            m_pagerLocalData.m_uNewActiveTileCount * sizeof(DUINT32));

        // Now prepare for requests. Check if we have enough tiles
        if (m_pagerStateData.m_uAvailableTileCount >= m_pagerLocalData.m_uNewlyRequiredTileCount)
        {
            nAvailableTileHndl = -1;

            // Prepare request list
            for (uI = 0U; uI < m_pagerLocalData.m_uNewlyRequiredTileCount; uI++)
            {
                bAlreadyRequested = false;

                // First of all check if this tile is already requested
                for (uJ = 0U; (uJ < m_pagerStateData.m_uRequestedTileCount) && (false == bAlreadyRequested); uJ++)
                {
                    if (m_pagerLocalData.m_aNewlyRequiredTiles[uI]
                        == m_pagerStateData.m_pReservedTiles[m_pagerStateData.m_pRequestedTiles[uJ]]->m_nTileID)
                    {
                        bAlreadyRequested = true;
                    }
                }

                // Allocate tile for each new request
                if ((false == bAlreadyRequested)
                    &&
                    (m_pagerStateData.m_uRequestedTileCount < G_PAGER_MAX_TILE_CAPACITY))
                {
                    // Current available tile handle
                    nAvailableTileHndl = m_pagerStateData.m_pAvailableTileIds[m_pagerStateData.m_uAvailableTileCount - 1U];

                    // Add to To Request list
                    m_pagerStateData.m_pTilesToRequest[m_pagerStateData.m_uTilesToRequestCount] = nAvailableTileHndl;

                    // Fill item with corresponding tile data
                    m_pagerStateData.m_pReservedTiles[nAvailableTileHndl]->m_nTileID
                        = m_pagerLocalData.m_aNewlyRequiredTiles[uI];

                    // Update stats
                    m_pagerStateData.m_uAvailableTileCount--;
                    m_pagerStateData.m_uTilesToRequestCount++;

                    //! FTODO: Remove later
                    if ((m_pagerStateData.m_uTilesToRequestCount > G_PAGER_MAX_TILE_CAPACITY)
                        ||
                        (m_pagerStateData.m_uAvailableTileCount < 0))
                    {
                        logError("[CPager::disposeActiveTiles] Error: m_uTilesToRequestCount:overflow, "
                            "m_uAvailableTileCount:underflow!");
                    }
                }
                else
                {
                    logError("[CPager::disposeAndPrepareRequests] CHECK ME Not enough tiles to allocate for request!");
                }
            }
        }
        else
        {
            logError("[CPager::disposeActiveTiles] Not engouh tiles to request!");
        }
    }
}

*/