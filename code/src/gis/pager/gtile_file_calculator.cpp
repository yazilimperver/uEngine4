#include <filesystem>
namespace fs = std::filesystem;

#include "gtile_file_calculator.h"

namespace gis {
    std::string GTileFileCalculator::Path(uint32_t zoomLevel, uint32_t row, uint32_t col) const {
        fs::path path(mRoot);

        path /= ("lvl" + std::to_string(zoomLevel));
        path /= std::to_string(row);
        path /= std::to_string(col);
        path += mExtension;

        return path.string();
    }
}