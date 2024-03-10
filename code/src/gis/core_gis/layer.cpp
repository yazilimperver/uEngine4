#include "layer.h"

bool gis::Layer::IsLayerVisible() const {
    return (Status() == LayerStatus::Visible);
}

std::string gis::Layer::Name() const {
    return mLayerName;
}

void gis::Layer::SetName(std::string_view layerName) {
    mLayerName = layerName;
}

gis::LayerStatus gis::Layer::Status() const {
    return mLayerStatus;
}

void gis::Layer::SetStatus(LayerStatus status) {
    mLayerStatus = status;
}

void gis::Layer::SetMetadata(const ParameterSet& layerMetadata) {
    mLayerMetadata = layerMetadata;
}

ParameterSet gis::Layer::Metadata() const {
    return mLayerMetadata;
}
