#include "raster_gl_layer.h"

#include "spdlog/spdlog.h"

#include "core_gis/raster_controller.h"
#include "raster_gl_renderer.h"

using namespace gis;

gis::RasterGLLayer::RasterGLLayer(std::shared_ptr<RasterController> controller, std::shared_ptr<RasterGLRenderer> renderer)
    : mRasterController(controller)
    , mRasterRenderer(renderer) {
}

bool gis::RasterGLLayer::Initialize() {
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

std::shared_ptr<LayerRenderer> gis::RasterGLLayer::Get2DRenderer() {
    return mRasterRenderer;
}

std::shared_ptr<LayerController> gis::RasterGLLayer::Get2DController(){
    return mRasterController;
}

LayerType gis::RasterGLLayer::GetLayerType() {
    return LayerType::Raster;
}

bool gis::RasterGLLayer::HasLayerLabelDisplay() const{
    return true;
}