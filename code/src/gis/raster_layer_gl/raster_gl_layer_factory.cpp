#include "raster_gl_layer_factory.h"

#include "spdlog/spdlog.h"

#include "utility/parameter_set.h"

#include "sdl_application/sdl_application.h"

#include "core_gis/tile_type.h"
#include "core_gis/raster_controller.h"

#include "raster_gl_layer.h"
#include "raster_gl_renderer.h"

const std::string gis::RasterGLLayerFactory::LayerTypeName{ "GoogleRasterGLLayer" };

std::string gis::RasterGLLayerFactory::LayerType() const {
    return LayerTypeName;
}

std::shared_ptr<gis::Layer> gis::RasterGLLayerFactory::CreateLayer(const ParameterSet layerMetadata) {
    auto rasterController = std::make_shared<gis::RasterController>();
    rasterController->SetSDLApplication(mSDLApplication);
    rasterController->SetMapView(mMapView);

    gis::TileType tileType;
    bool useGLRenderer;
    bool isOnline;
    uint32_t tileSize;
    uint32_t minZoom, maxZoom;
    double transparency;
    std::string path, extension, name;

    layerMetadata.GetParameterValue<gis::TileType>("TileType", tileType);
    layerMetadata.GetParameterValue<bool>("IsOnline", isOnline);
    layerMetadata.GetParameterValue<bool>("UseGLRenderer", useGLRenderer);
    layerMetadata.GetParameterValue<uint32_t>("TileSize", tileSize);
    layerMetadata.GetParameterValue<uint32_t>("MinZoomLevel", minZoom);
    layerMetadata.GetParameterValue<uint32_t>("MaxZoomLevel", maxZoom);
    layerMetadata.GetParameterValue<double>("Transparency", transparency);
    layerMetadata.GetParameterValue<std::string>("Path", path);
    layerMetadata.GetParameterValue<std::string>("Extension", extension);
    layerMetadata.GetParameterValue<std::string>("Name", name);

    rasterController->SetTileSize(tileSize);
    rasterController->SetSourceInfo(isOnline, path, extension);
    rasterController->SetAssetSerivce(&mSDLApplication->AssetService());

    if (true == useGLRenderer) {
        rasterController->SetLoaderName("STBImageLoader");

        spdlog::info("Raster layer with GL renderer will be used!");
        auto rasterGLRenderer = std::make_shared<gis::RasterGLRenderer>();
        rasterGLRenderer->SetSDLApplication(mSDLApplication);
        rasterGLRenderer->SetMapView(mMapView);
        rasterGLRenderer->SetTileSize(tileSize);
        rasterGLRenderer->SetTransparency(transparency);
        rasterGLRenderer->SetMinMaxZoom(minZoom, maxZoom);
        rasterGLRenderer->SetPainter(mPainter);

        auto rasterLayer = std::make_shared<RasterGLLayer>(rasterController, rasterGLRenderer);
        rasterLayer->SetLayerName(name);
        return rasterLayer;
    }
    else {
        spdlog::info("Incorrect display infrasturcture provided!");
        return nullptr;
    }
}

void gis::RasterGLLayerFactory::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterGLLayerFactory::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}

void gis::RasterGLLayerFactory::SetPainter(std::shared_ptr<gl::GLBasicPainter> painter) {
    mPainter = painter;
}
