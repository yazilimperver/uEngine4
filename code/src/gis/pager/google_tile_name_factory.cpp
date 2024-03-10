#include "google_tile_name_factory.h"

#include "gtile_file_calculator.h"

namespace gis {
    std::shared_ptr<TileNameCalculator> GoogleTileNameFactory::CreateTileNameCalculator(std::string_view  extension, std::string_view root) {
        return std::make_shared<GTileFileCalculator>(extension, root);
    }
}