#include <filesystem>
namespace fs = std::filesystem;

#include "gtile_file_calculator.h"

namespace gis {

    static std::string FactoryLayerTypeName{ "GoogleRasterGLLayer" };

    GTileFileCalculator::GTileFileCalculator(std::string_view extension, std::string_view root)
        : TileNameCalculator(extension, root) { }

    std::string GTileFileCalculator::LayerType() const  {
        return FactoryLayerTypeName;
    }

    std::string GTileFileCalculator::Path(uint32_t zoomLevel, uint32_t row, uint32_t col) const {
        fs::path path(mRoot);

        path /= ("lvl" + std::to_string(zoomLevel));
        path /= std::to_string(row);
        path /= std::to_string(col);
        path += mExtension;

        return path.string();
    }
}