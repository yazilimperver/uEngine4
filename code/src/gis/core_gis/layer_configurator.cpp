#include "layer_configurator.h"

#include "layer_service.h"

#include "layer_configurator_serializer.h"

#include "utility/json_data_parser.h"

#include "utility/parameter_set.h"

namespace gis {
    LayerConfigurator::LayerConfigurator(LayerService* layerService)
        : mLayerService(layerService) {
    }

    void LayerConfigurator::Configure(std::string_view layerConfigurationPath) {
        JsonDataParser<LayerConfiguration> layerConfigurationParser;

        auto opResult = layerConfigurationParser.Deserialize(layerConfigurationPath);

        if (true == opResult.has_value()) {
            auto layerConfiguration = opResult.value();
            
            // Raster katmanlarini olusturalim
            for ( auto& metadata : layerConfiguration.RasterLayers) {
                CreateLayer(metadata);
            }
        } 
        else {
            // hata durumlarina bakalim sonra
        }
    }
    
    void LayerConfigurator::CreateLayer(const RasterLayerMetadata& metadata)    {
        ParameterSet rasterDataSet;

        rasterDataSet.UpdateParameterValue("LayerFactory", metadata.LayerFactory);
        rasterDataSet.UpdateParameterValue("TileType", metadata.TileType);
        rasterDataSet.UpdateParameterValue("IsOnline", metadata.IsOnline);
        rasterDataSet.UpdateParameterValue("InitialVisibility", metadata.InitialVisibility);
        rasterDataSet.UpdateParameterValue("UseGLRenderer", metadata.UseGLRenderer);
        rasterDataSet.UpdateParameterValue("TileSize", metadata.TileSize);
        rasterDataSet.UpdateParameterValue("MinZoomLevel", metadata.MinZoomLevel);
        rasterDataSet.UpdateParameterValue("MaxZoomLevel", metadata.MaxZoomLevel);
        rasterDataSet.UpdateParameterValue("Priority", metadata.Priority);
        rasterDataSet.UpdateParameterValue("Transparency", metadata.Transparency);
        rasterDataSet.UpdateParameterValue("Path", metadata.Path);
        rasterDataSet.UpdateParameterValue("Name", metadata.Name);
        rasterDataSet.UpdateParameterValue("Extension", metadata.Extension);

        mLayerService->CreateLayer(metadata.Name, rasterDataSet);
    }
}