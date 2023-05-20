#include "raster_controller.h"

#include "spdlog/spdlog.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;

static const uint32_t cTileSize{ 256 };

bool gis::RasterController::IsInitialized() {
    return mIsInitialized;
}

void gis::RasterController::DetermineTileCount() {
	// Optimum (tek sayi) pafta adetlerini belirleyelim
	uint32_t tileCount = (std::max(mMapView->WinWidth(), mMapView->WinHeight()) / cTileSize);

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
        // Pager nesnesini ilk kontrolcude olusturup diger siniflara v eriyoruz
		mPager = std::make_shared<gis::Pager>();

		DetermineTileCount();
		mTileIdCalculator = std::make_unique<gis::GTileFileCalculator>(".png", R"(D:\git_repos\Yazilimperver\uEngine4\assets\map_data\google_raster\)");

		mMapLoader.AssignRenderer(mSDLApplication->GetSdlRenderer());

		// Pager'a iliskin ayarlamalari yapalim
		mPager->AssignListener(this);
		mPager->SetOrigin(gis::TileOrigin::Google);
		mPager->SetTilePerAxis(mTilePerAxis);

		// Ilk paftalari yuklettirelim
		TriggerPager();

		mIsInitialized = true;
    }

    return mIsInitialized;
}

void gis::RasterController::Update() {
    mPager->UpdateReference(mMapView->CenterInPixels(), mMapView->ZoomLevel());
    mPager->Update();
}

void gis::RasterController::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterController::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}

void gis::RasterController::SetRasterRenderer(std::shared_ptr<RasterSDLRenderer> renderer) {
	mRasterRenderer = renderer;
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
			mMapLoader.Dispose(std::move(mRasterAssets.at(tile)));
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

			mRasterAssets.emplace(tile, mMapLoader.Load(mTileIdCalculator->Path(mMapView->ZoomLevel(), tile.TileX, tile.TileY), "raster_tile"));
		}

		spdlog::info(tileListStr);
	}
}
