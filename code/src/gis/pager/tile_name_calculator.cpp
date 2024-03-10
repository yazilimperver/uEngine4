#include "tile_name_calculator.h"

gis::TileNameCalculator::TileNameCalculator(std::string_view extension, std::string_view root)
    : mExtension(extension.data())
    , mRoot(root.data()) {
}

std::string gis::TileNameCalculator::Root() const {
    return mRoot;
}

std::string gis::TileNameCalculator::Extension() const {
    return mExtension;
}

void gis::TileNameCalculator::SetRoot(std::string_view root) {
    mRoot = static_cast<std::string>(root);
}

void gis::TileNameCalculator::SetExtension(std::string_view extension) {
    mExtension = static_cast<std::string>(extension);
}
