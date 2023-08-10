#include "raster_gl_renderer.h"

#include "spdlog/spdlog.h"

#include "painter/gfx_primitives.h"

#include "gl_texture/texture_asset.h"

#include "gis_asset/gis_map_asset.h"

#include "sdl_application/sdl_application.h"

using namespace basic_engine;
using namespace gis_asset;
bool gis::RasterGLRenderer ::Initialize() {
    if ((mPager != nullptr)
        &&
        (mMapView != nullptr)
        &&
        (mRasterAssets != nullptr)
        &&
        (mSDLApplication != nullptr)) {
        mScreenCenter.x = mSDLApplication->GetWindowParametrs().Width / 2;
        mScreenCenter.y = mSDLApplication->GetWindowParametrs().Height / 2;

        mIsInitialized = true;
    }
    else {
        spdlog::info("Raster SDL Renderer initialization failed!");
    }

    return mIsInitialized;
}

void gis::RasterGLRenderer ::DisplayGeometry() {
    mGLPainter->SaveState();
    mGLPainter->ResetTransform();

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

            infra::Rectangle<float> tileRect{ static_cast<float>(std::get<0>(tileBound).x - viewCenter.x + mScreenCenter.x),
                static_cast<float>(std::get<0>(tileBound).y - viewCenter.y + mScreenCenter.y), 
                static_cast<float>(mTileSize), 
                static_cast<float>(mTileSize) };

            if (true == mEnableDebugInfo) {
                mGLPainter->SetPen(gl::Pen{ gl::PenStyle::SolidLine, Color::Blue, 3 });
                mGLPainter->DrawRect(tileRect);
            }

            gis::TileId tileToDisplay{ googleTileX, googleTileY, zoomLevel };
            
            if (mRasterAssets->contains(tileToDisplay)) {
                auto gisAsset = std::static_pointer_cast<gl::TextureAsset>(mRasterAssets->at(tileToDisplay));

                if (nullptr != gisAsset && infra::AssetStatus::LoadSuccessful == gisAsset->Info().mStatus) {
                    gisAsset->BindTexture();
                    mGLPainter->DrawTexture(gisAsset.get(),
                        { tileRect.Left + mTileSize * 0.5, tileRect.Top + mTileSize * 0.5},
                        static_cast<float>(gisAsset->GetTextureInfo().Width),
                        static_cast<float>(gisAsset->GetTextureInfo().Height));
                }
            }

            if (true == mEnableDebugInfo) {
                char tileStr[128];
                sprintf(tileStr, "GGL:<%d, %d>", googleTileX, googleTileY);
                
                mGLPainter->SetPen(gl::Pen{ gl::PenStyle::SolidLine, Color::Red, 3 });
                mGLPainter->SimpleText({ tileRect.Left + mTileSize * 0.25, tileRect.Top + mTileSize * 0.45 }, tileStr);
            }

            googleTileX++;
        }

        googleTileY++;
    }

    mGLPainter->RestoreState();
}

void gis::RasterGLRenderer ::DisplayLabel() {
    auto zoomLevel = mMapView->ZoomLevel();
    if (zoomLevel < std::get<0>(mMinMaxZoom)
        || zoomLevel > std::get<1>(mMinMaxZoom))
        return;
}

void gis::RasterGLRenderer ::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}

void gis::RasterGLRenderer ::SetPager(std::shared_ptr<gis::Pager> pager) {
    mPager = pager;
}

void gis::RasterGLRenderer ::SetMinMaxZoom(uint32_t minZoom, uint32_t maxZoom) {
    mMinMaxZoom = std::make_pair(minZoom, maxZoom);
}

void gis::RasterGLRenderer ::SetTransparency(double transparency) {
    mTransparency = transparency;
}

void gis::RasterGLRenderer ::SetTileSize(uint32_t tileSize) {
    mTileSize = tileSize;
}

void gis::RasterGLRenderer ::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterGLRenderer ::SetRasterAssets(const GisRasterTileHashDictionary* assets) {
    mRasterAssets = assets;
}

void gis::RasterGLRenderer ::SetDebugInfoVisibility(bool visibility) {
    mEnableDebugInfo = visibility;
}

void gis::RasterGLRenderer::SetPainter(std::shared_ptr<gl::GLBasicPainter> painter) {
    mGLPainter = painter;
}
