#include "raster_sdl_layer.h"

#include "spdlog/spdlog.h"

#include "core_gis/raster_controller.h"
#include "raster_sdl_renderer.h"

using namespace gis;

gis::RasterSDLLayer::RasterSDLLayer(std::shared_ptr<RasterController> controller, std::shared_ptr<RasterSDLRenderer> renderer)
    : mRasterController(controller)
    , mRasterRenderer(renderer) {
}

bool gis::RasterSDLLayer::Initialize() {
    bool isInitialized = false;

    // Once kontrolcuyu ilklendirelim
    if (nullptr != mRasterController && nullptr != mRasterRenderer) {
        isInitialized = mRasterController->Initialize();

        if (isInitialized) {
            // Raster kontrolcusunden ilgili huuslari alalim
            mRasterRenderer->SetPager(mRasterController->GetPager());
            mRasterRenderer->SetRasterAssets(mRasterController->GetRasterTileAssets());

            isInitialized = mRasterRenderer->Initialize();
        }
    }

    return isInitialized;
}

std::shared_ptr<LayerRenderer> gis::RasterSDLLayer::Get2DRenderer() {
    return mRasterRenderer;
}

std::shared_ptr<LayerController> gis::RasterSDLLayer::Get2DController(){
    return mRasterController;
}

LayerType gis::RasterSDLLayer::GetLayerType() {
    return LayerType::Raster;
}

bool gis::RasterSDLLayer::HasLayerLabelDisplay() const{
    return true;
}