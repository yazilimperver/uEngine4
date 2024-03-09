#include "layer_configurator.h"

#include "spdlog/spdlog.h"

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
             
            // Vektor katmanlarini olusturalim
            for (auto& metadata : layerConfiguration.VectorLayers) {
                CreateLayer(metadata);
            }

            // Kullanici katmanlarini olusturalim
            for (auto& metadata : layerConfiguration.CustomLayers) {
                CreateLayer(metadata); 
            }

            // TODO: Yukseklik, vektor katmanlar
        } 
        else {
            // hata durumlarina bakalim sonra
            spdlog::error("Layer deserialization failed for given configuration: {}", static_cast<std::string>(layerConfigurationPath));
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

    void LayerConfigurator::CreateLayer(const VectorLayerMetadata& metadata) {
        ParameterSet vectorDataSet;

        vectorDataSet.UpdateParameterValue("LayerFactory", metadata.LayerFactory);
        vectorDataSet.UpdateParameterValue("IsOnline", metadata.IsOnline);
        vectorDataSet.UpdateParameterValue("InitialVisibility", metadata.InitialVisibility);
        vectorDataSet.UpdateParameterValue("UseGLRenderer", metadata.UseGLRenderer);
        vectorDataSet.UpdateParameterValue("MinZoomLevel", metadata.MinZoomLevel);
        vectorDataSet.UpdateParameterValue("MaxZoomLevel", metadata.MaxZoomLevel);
        vectorDataSet.UpdateParameterValue("Priority", metadata.Priority);
        vectorDataSet.UpdateParameterValue("Transparency", metadata.Transparency);
        vectorDataSet.UpdateParameterValue("Path", metadata.Path);
        vectorDataSet.UpdateParameterValue("Name", metadata.Name);
        vectorDataSet.UpdateParameterValue("LabelFieldName", metadata.LabelFieldName);
        vectorDataSet.UpdateParameterValue("Extension", metadata.Extension);

        mLayerService->CreateLayer(metadata.Name, vectorDataSet);
    }

    void LayerConfigurator::CreateLayer(const CustomLayerMetadata& metadata)     {
        ParameterSet customDataSet;

        customDataSet.UpdateParameterValue("LayerFactory", metadata.LayerFactory);
        customDataSet.UpdateParameterValue("InitialVisibility", metadata.InitialVisibility);
        customDataSet.UpdateParameterValue("Priority", metadata.Priority);
        customDataSet.UpdateParameterValue("Name", metadata.Name);

        mLayerService->CreateLayer(metadata.Name, customDataSet);
    }
}