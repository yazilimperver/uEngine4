#include "raster_controller.h"

#include "spdlog/spdlog.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;

bool gis::RasterController::IsInitialized() {
    return mIsInitialized;
}

void gis::RasterController::DetermineTileCount() {
    // Optimum (tek sayi) pafta adetlerini belirleyelim
    uint32_t tileCount = (std::max(mMapView->WinWidth(), mMapView->WinHeight()) / mTileSize);

    if (0 == (tileCount % 2)) {
        tileCount++;
    }
    // Pan sirasinda bosluk olusmamasi icin ekstra yukleyelim
    tileCount += 2;

    spdlog::info("Determined tile count: {}", tileCount);
    mTilePerAxis = tileCount;
}

void gis::RasterController::TriggerPager() {
    // Bir kerelik pager'i tetikleyelim
    mPager->UpdateReference(mMapView->CenterInPixels(), mMapView->ZoomLevel());
    mPager->Update();
}

bool gis::RasterController::Initialize() {
    if ((mMapView != nullptr) &&
        (mSDLApplication != nullptr)) {
        
        if (auto loaderHandle = mAssetService->LoaderHandle(mLoaderName); loaderHandle.has_value()) {
            mLoaderHandle = loaderHandle.value();

            // Pager nesnesini ilk kontrolcude olusturup diger siniflara v eriyoruz
            mPager = std::make_shared<gis::Pager>();

            DetermineTileCount();
            mTileIdCalculator = std::make_unique<gis::GTileFileCalculator>(mExtension, mPath);

            // Pager'a iliskin ayarlamalari yapalim
            mPager->AssignListener(this);
            mPager->SetOrigin(gis::TileOrigin::Google);
            mPager->SetTilePerAxis(mTilePerAxis);

            // Ilk paftalari yuklettirelim
            TriggerPager();

            mIsInitialized = true;
        }
        else {
            spdlog::error("Provided loader not found! Loader name: {}", mLoaderName);
        }
    }

    return mIsInitialized;
}

void gis::RasterController::Update() {
    mPager->UpdateReference(mMapView->CenterInPixels(), mMapView->ZoomLevel());
    mPager->Update();
}

void gis::RasterController::SetLoaderName(std::string_view name) {
    mLoaderName = static_cast<std::string>(name);
}

void gis::RasterController::SetTileSize(uint32_t tileSize) {
    mTileSize = tileSize;
}

void gis::RasterController::SetSourceInfo(bool isOnline, std::string_view path, std::string_view extension) {
    mIsOnline = isOnline;
    mPath = static_cast<std::string>(path);
    mExtension = static_cast<std::string>(extension);
}

void gis::RasterController::SetAssetSerivce(infra::AssetService* assetService) {
    mAssetService = assetService;
}

void gis::RasterController::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterController::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}
std::shared_ptr<gis::Pager> gis::RasterController::GetPager() {
    return mPager;
}

const GisRasterTileHashDictionary* gis::RasterController::GetRasterTileAssets() const {
    return &mRasterAssets;
}

void gis::RasterController::PagedTilesUpdated() {
    auto tilesToDispose = mPager->TilesToDispose();
    {
        std::string tileListStr = "Tiles To Dispose: ";
        for (auto tile : tilesToDispose) {
            tileListStr += fmt::format("<{}-{}/{}>,", tile.TileX, tile.TileY, tile.ZoomLevel);
            mAssetService->DisposeAsset(mRasterAssets.at(tile)->Info().mHandle);
            mRasterAssets.erase(tile);
        }

        spdlog::info(tileListStr);
    }

    spdlog::info("Paged tiles are updated!");
    auto tilesToLoad = mPager->TilesToLoad();
    {
        std::string tileListStr = "Tiles To Load: ";
        for (auto tile : tilesToLoad) {
            tileListStr += fmt::format("<{}-{}/{}>,", tile.TileX, tile.TileY, tile.ZoomLevel);

            auto assetHandle = mAssetService->LoadAsset(mLoaderHandle, mTileIdCalculator->Path(mMapView->ZoomLevel(), tile.TileX, tile.TileY), "raster_tile");

            if (assetHandle.has_value()) {
                mRasterAssets.emplace(tile, mAssetService->SharedAsset(assetHandle.value()));
            }
        }

        spdlog::info(tileListStr);
    }
}
