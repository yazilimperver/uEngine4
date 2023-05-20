#include "raster_layer_factory.h"

#include "raster_layer.h"
#include "raster_controller.h"
#include "raster_sdl_renderer.h"

#include "sdl_application/sdl_application.h"

const std::string gis::RasterLayerFactory::LayerTypeName{ "GoogleRasterLayer" };

std::string gis::RasterLayerFactory::LayerType() const {
    return LayerTypeName;
}

std::shared_ptr<gis::Layer> gis::RasterLayerFactory::CreateLayer(std::string_view layerName) {
    auto rasterController = std::make_shared<gis::RasterController>();
    rasterController->SetSDLApplication(mSDLApplication);
    rasterController->SetMapView(mMapView);

    auto rasterSDLRenderer = std::make_shared<gis::RasterSDLRenderer>();
    rasterSDLRenderer->SetSDLApplication(mSDLApplication);
    rasterSDLRenderer->SetMapView(mMapView);

    rasterController->SetRasterRenderer(rasterSDLRenderer);

    auto rasterLayer = std::make_shared<RasterLayer>(rasterController, rasterSDLRenderer);
    rasterLayer->SetLayerName(layerName);
    return rasterLayer;
}

void gis::RasterLayerFactory::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterLayerFactory::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}
