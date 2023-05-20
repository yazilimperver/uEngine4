#include "raster_sdl_renderer.h"

#include "SDL.h"

#include "spdlog/spdlog.h"
#include "painter/gfx_primitives.h"
#include "gis_asset/gis_map_asset.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;
using namespace gis_asset;

const uint32_t cTileSize{ 256 };

bool gis::RasterSDLRenderer::Initialize() {
    if ((mPager != nullptr)
        &&
        (mMapView != nullptr)
        &&
        (mRasterAssets != nullptr)
		&&
		(mSDLApplication != nullptr)) {
		mRenderer = mSDLApplication->GetSdlRenderer();
		mWindow = mSDLApplication->GetSdlWindow();
		mScreenCenter.x = mSDLApplication->GetWindowParametrs().Width / 2;
		mScreenCenter.y = mSDLApplication->GetWindowParametrs().Height / 2;

		// Gosterim icin kullanacagimiz sinif
		mPainter.AssignRenderer(mRenderer);

        mIsInitialized = true;
    }
    else {
        spdlog::info("Raster SDL Renderer initialization failed!");
    }

    return mIsInitialized;
}

void gis::RasterSDLRenderer::DisplayGeometry() {
    int32_t tilePerAxis = mPager->TilePerAxis();
	int32_t radius = tilePerAxis / 2;
	auto zoomLevel = mMapView->ZoomLevel();
    PointInPixels viewCenter = mMapView->CenterInPixels();
    auto calculatedCenterTileInfo = gis::TileTms::PixelToTile(viewCenter, zoomLevel).ObtainGoogleTileInfo();
	int32_t googleTileX = calculatedCenterTileInfo.x;
	int32_t googleTileY = calculatedCenterTileInfo.y - radius;

	for (int32_t i = 0; i < tilePerAxis; i++) {
		googleTileX = calculatedCenterTileInfo.x - radius;

		for (int32_t j = 0; j < tilePerAxis; j++) {

			auto tileToUse = gis::TileTms::FromGoogleTile({ googleTileX, googleTileY }, mMapView->ZoomLevel());
			auto tileBound = tileToUse.PixelBoundsTopLeftBottomRigth();

			SDL_Rect tileRect{ std::get<0>(tileBound).x - viewCenter.x + mScreenCenter.x,
							   std::get<0>(tileBound).y - viewCenter.y + mScreenCenter.y, cTileSize, cTileSize };

			if (true == mEnableInfo) {
				mPainter.AssignPen(Pen{ Color::Blue, 3 });
				mPainter.DrawRectangle(tileRect);
			}

			gis::TileId tileToDisplay{ googleTileX, googleTileY, zoomLevel };
			if (mRasterAssets->contains(tileToDisplay)) {
				auto gisAsset = dynamic_cast<GisMapAsset*>(mRasterAssets->at(tileToDisplay).get());

				if (nullptr != gisAsset) {
					mPainter.DrawTexture(gisAsset->Texture(), { static_cast<Sint16>(tileRect.x + cTileSize * 0.5), static_cast<Sint16>(tileRect.y + cTileSize * 0.5) }, gisAsset->Width(), gisAsset->Height());
				}
			}

			if (true == mEnableInfo) {
				char tileStr[128];
				sprintf(tileStr, "GGL:<%d, %d>", googleTileX, googleTileY);
				stringRGBA(mRenderer, static_cast<Sint16>(tileRect.x + cTileSize * 0.5), static_cast<Sint16>(tileRect.y + cTileSize * 0.55), tileStr, 255, 0, 0, 255);
			}

			googleTileX++;
		}

		googleTileY++;
	}

}

void gis::RasterSDLRenderer::DisplayLabel() {
}

void gis::RasterSDLRenderer::SetMapView(std::shared_ptr<gis::MapView> mapView) {
	mMapView = mapView;
}

void gis::RasterSDLRenderer::SetPager(std::shared_ptr<gis::Pager> pager) {
	mPager = pager;
}

void gis::RasterSDLRenderer::SetSDLApplication(SdlApplication* sdlApplication) {
	mSDLApplication = sdlApplication;
}

void gis::RasterSDLRenderer::SetRasterAssets(const GisRasterTileHashDictionary* assets) {
    mRasterAssets = assets;
}
