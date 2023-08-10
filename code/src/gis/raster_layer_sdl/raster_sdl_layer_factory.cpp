#include "raster_sdl_layer_factory.h"

#include "spdlog/spdlog.h"

#include "utility/parameter_set.h"

#include "sdl_application/sdl_application.h"

#include "core_gis/tile_type.h"
#include "core_gis/raster_controller.h"

#include "raster_sdl_layer.h"
#include "raster_sdl_renderer.h"

const std::string gis::RasterSDLLayerFactory::LayerTypeName{ "GoogleRasterSDLLayer" };

std::string gis::RasterSDLLayerFactory::LayerType() const {
    return LayerTypeName;
}

std::shared_ptr<gis::Layer> gis::RasterSDLLayerFactory::CreateLayer(const ParameterSet layerMetadata) {
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

    if (false == useGLRenderer) {
        rasterController->SetLoaderName("SdlTexture");

        spdlog::info("Raster layer with SDL renderer will be used!");
        auto rasterSDLRenderer = std::make_shared<gis::RasterSDLRenderer>();
        rasterSDLRenderer->SetSDLApplication(mSDLApplication);
        rasterSDLRenderer->SetMapView(mMapView);
        rasterSDLRenderer->SetTileSize(tileSize);
        rasterSDLRenderer->SetTransparency(transparency);
        rasterSDLRenderer->SetMinMaxZoom(minZoom, maxZoom);
        rasterSDLRenderer->SetPainter(mSDLPainter);

        auto rasterLayer = std::make_shared<RasterSDLLayer>(rasterController, rasterSDLRenderer);
        rasterLayer->SetLayerName(name);
        return rasterLayer;
    }
    else {
        spdlog::info("Incorrect display infrastructure provided!");
        return nullptr;
    }
}

void gis::RasterSDLLayerFactory::SetSDLApplication(SdlApplication* sdlApplication) {
    mSDLApplication = sdlApplication;
}

void gis::RasterSDLLayerFactory::SetMapView(std::shared_ptr<gis::MapView> mapView) {
    mMapView = mapView;
}

void gis::RasterSDLLayerFactory::SetPainter(std::shared_ptr<basic_engine::Painter> painter) {
    mSDLPainter = painter;
}
