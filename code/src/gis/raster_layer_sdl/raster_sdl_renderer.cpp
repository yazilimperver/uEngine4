#include "raster_sdl_renderer.h"

#include "SDL.h"

#include "spdlog/spdlog.h"
#include "painter/gfx_primitives.h"

#include "sdl_asset/sdl_texture_asset.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;
using namespace gis_asset;
bool gis::RasterSDLRenderer::Initialize() {
    if ((mPager != nullptr)
        &&
        (mMapView != nullptr)
        &&
        (mRasterAssets != nullptr)
		&&
		(mSDLApplication != nullptr)) {
		mRenderer = mSDLApplication->GetSdlRenderer();
		mScreenCenter.x = mSDLApplication->GetWindowParametrs().Width / 2;
		mScreenCenter.y = mSDLApplication->GetWindowParametrs().Height / 2;

        mIsInitialized = true;
    }
    else {
        spdlog::info("Raster SDL Renderer initialization failed!");
    }

    return mIsInitialized;
}

void gis::RasterSDLRenderer::DisplayGeometry() {
	auto zoomLevel = mMapView->ZoomLevel();

	if (zoomLevel < std::get<0>(mMinMaxZoom)
		|| zoomLevel > std::get<1>(mMinMaxZoom))
		return;


    int32_t tilePerAxis = mPager->TilePerAxis();
	int32_t radius = tilePerAxis / 2;
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
							   std::get<0>(tileBound).y - viewCenter.y + mScreenCenter.y, 
                               static_cast<int32_t>(mTileSize), static_cast<int32_t>(mTileSize) };

			if (true == mEnableDebugInfo) {
				mSDLPainter->AssignPen(Pen{ Color::Blue, 3 });
				mSDLPainter->DrawRectangle(tileRect);
			}

			gis::TileId tileToDisplay{ googleTileX, googleTileY, zoomLevel };
			if (mRasterAssets->contains(tileToDisplay)) {
                auto gisAsset = std::static_pointer_cast<basic_engine::SdlTextureAsset>(mRasterAssets->at(tileToDisplay));

				if (nullptr != gisAsset) {
					SDL_SetTextureBlendMode(gisAsset->Texture(), SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(gisAsset->Texture(), static_cast<uint8_t>(mTransparency * 255));
					mSDLPainter->DrawTexture(gisAsset->Texture(), { static_cast<Sint16>(tileRect.x + mTileSize * 0.5), 
						static_cast<Sint16>(tileRect.y + mTileSize * 0.5) }, 
						gisAsset->Width(), gisAsset->Height());
				}
			}

			if (true == mEnableDebugInfo) {
				char tileStr[128];
				sprintf(tileStr, "GGL:<%d, %d>", googleTileX, googleTileY);
				stringRGBA(mRenderer, 
					static_cast<Sint16>(tileRect.x + mTileSize * 0.5), 
					static_cast<Sint16>(tileRect.y + mTileSize * 0.55),
					tileStr, 255, 0, 0, 255);
			}

			googleTileX++;
		}

		googleTileY++;
	}
}

void gis::RasterSDLRenderer::DisplayLabel() {
	auto zoomLevel = mMapView->ZoomLevel();
	if (zoomLevel < std::get<0>(mMinMaxZoom)
		|| zoomLevel > std::get<1>(mMinMaxZoom))
		return;
}

void gis::RasterSDLRenderer::SetMapView(std::shared_ptr<gis::MapView> mapView) {
	mMapView = mapView;
}

void gis::RasterSDLRenderer::SetPager(std::shared_ptr<gis::Pager> pager) {
	mPager = pager;
}

void gis::RasterSDLRenderer::SetMinMaxZoom(uint32_t minZoom, uint32_t maxZoom) {
	mMinMaxZoom = std::make_pair(minZoom, maxZoom);
}

void gis::RasterSDLRenderer::SetTransparency(double transparency) {
	mTransparency = transparency;
}

void gis::RasterSDLRenderer::SetTileSize(uint32_t tileSize) {
	mTileSize = tileSize;
}

void gis::RasterSDLRenderer::SetSDLApplication(SdlApplication* sdlApplication) {
	mSDLApplication = sdlApplication;
}

void gis::RasterSDLRenderer::SetRasterAssets(const GisRasterTileHashDictionary* assets) {
    mRasterAssets = assets;
}

void gis::RasterSDLRenderer::SetDebugInfoVisibility(bool visibility) {
	mEnableDebugInfo = visibility;
}

void gis::RasterSDLRenderer::SetPainter(std::shared_ptr<basic_engine::Painter> painter) {
    mSDLPainter = painter;
}