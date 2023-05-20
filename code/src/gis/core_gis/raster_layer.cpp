#include "raster_layer.h"

#include "spdlog/spdlog.h"

#include "raster_controller.h"
#include "raster_sdl_renderer.h"

using namespace gis;

gis::RasterLayer::RasterLayer(std::shared_ptr<RasterController> controller, std::shared_ptr<RasterSDLRenderer> renderer)
    : mRasterController(controller)
    , mRasterRenderer(renderer) {
}

bool gis::RasterLayer::Initialize() {
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

std::shared_ptr<LayerRenderer> gis::RasterLayer::Get2DRenderer() {
    return mRasterRenderer;
}

std::shared_ptr<LayerController> gis::RasterLayer::Get2DController(){
    return mRasterController;
}

LayerType gis::RasterLayer::GetLayerType() {
    return LayerType::Raster;
}

LayerStatus gis::RasterLayer::GetLayerStatus() const{
    return mLayerStatus;
}

std::string gis::RasterLayer::GetLayerName() const{
    return mLayerName;
}

bool gis::RasterLayer::HasLayerLabelDisplay() const{
    return true;
}

void gis::RasterLayer::SetLayerStatus(LayerStatus status) {
    mLayerStatus = status;
}

void gis::RasterLayer::SetLayerName(std::string_view layerName) {
    mLayerName = layerName.data();
}
