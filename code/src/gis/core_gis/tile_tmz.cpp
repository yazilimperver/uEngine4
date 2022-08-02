#include "tile_tmz.h"

namespace gis {
    TileTmz::TileTmz(int32_t tmsX, int32_t tmsY, uint32_t zoom)
        : mTmsX{ tmsX }, mTmsY{ tmsY }, mZoom{ zoom } { }

    TileTmz TileTmz::FromTmsTileInfo(const TmsTileInfo& tmsTileInfo, uint32_t zoom) {
        return { tmsTileInfo.x, tmsTileInfo.y, zoom };
    }

    TileTmz TileTmz::FromGoogleTile(const GoogleTileInfo& googleTile, uint32_t zoom) {
        int32_t tmsY = (1 << zoom) - 1 - googleTile.y;
        return FromTmsTileInfo(TmsTileInfo{ googleTile.x, tmsY }, zoom);
    }

    TileTmz TileTmz::QuadTreeToTile(const std::string& quadTree) {
        int32_t zoom = static_cast<int32_t>(quadTree.size());
        auto offset = (1 << zoom) - 1;

        std::vector<int32_t> digits{};
        transform(cbegin(quadTree), cend(quadTree), std::back_inserter(digits), [](auto c) {
            return c - '0';
            });

        auto [googleX, googleY] = std::accumulate(cbegin(digits), cend(digits), std::pair{ 0, 0 }, [](auto acc, auto digit) {
            auto quotient = digit / 2;
            auto remainder = digit % 2;
            return std::pair{ (acc.first << 1) | remainder, (acc.second << 1) | quotient };
            });

        int32_t tmsY = offset - googleY;
        return TileTmz::FromTmsTileInfo(TmsTileInfo{ googleX, tmsY }, zoom);
    }

    TileTmz TileTmz::GeographicToTile(const GeoPoint& pointInGeog, uint32_t zoom) {
        auto pointInPixel = SlippyMapUtil::GeographicToPixel(pointInGeog, zoom);
        return TileTmz::PixelToTile(pointInPixel, zoom);

    }

    TileTmz TileTmz::MeterToTile(const PointInMeters& pointInMeter, uint32_t zoom) {
        auto pointInPixel = SlippyMapUtil::MeterToPixels(pointInMeter, zoom);
        return TileTmz::PixelToTile(pointInPixel, zoom);
    }

    TileTmz TileTmz::PixelToTile(const PointInPixels& inputInPixel, uint32_t zoom) {
        auto tmsX = static_cast<int>(std::ceil(inputInPixel.x / static_cast<double>(cDefaultTileSize)) - 1);
        auto tmsY = static_cast<int>(std::ceil(inputInPixel.y / static_cast<double>(cDefaultTileSize)) - 1);
        tmsY = (1 << zoom) - 1 - tmsY;
        return TileTmz::FromTmsTileInfo(TmsTileInfo{ tmsX, tmsY }, zoom);
    }

    MercatorRectangle TileTmz::MercatorBounds() {
        auto pixelMin = SlippyMapUtil::PixelToMeter({ mTmsX * cDefaultTileSize, mTmsY * cDefaultTileSize }, mZoom);
        auto pixelMax = SlippyMapUtil::PixelToMeter({ (mTmsX + 1) * cDefaultTileSize, (mTmsY + 1) * cDefaultTileSize }, mZoom);

        return { pixelMin, pixelMax };
    }

    GeoRectangle TileTmz::GeographicBounds() {
        auto googleTileInfo = ObtainGoogleTileInfo();

        auto pixelXWest = googleTileInfo.x * cDefaultTileSize;
        auto pixelYNorth = googleTileInfo.y * cDefaultTileSize;

        auto pixelXEast = (googleTileInfo.x + 1) * cDefaultTileSize;
        auto pixelYSouth = (googleTileInfo.y + 1) * cDefaultTileSize;

        auto pointMin = SlippyMapUtil::PixelToGeographic(PointInPixels{ pixelXWest, pixelYSouth }, mZoom);
        auto pointMax = SlippyMapUtil::PixelToGeographic(PointInPixels{ pixelXEast, pixelYNorth }, mZoom);

        return { pointMin, pointMax };
    }

    TmsTileInfo TileTmz::TileInfo() const{
        return { mTmsX, mTmsY };
    }

    GoogleTileInfo TileTmz::ObtainGoogleTileInfo() const {
        auto googleY = (1 << mZoom) - 1 - mTmsY;
        return { mTmsX, googleY };
    }

    std::string TileTmz::QuadTreeRepresentation() const {
        int32_t tmsX = mTmsX;
        int32_t tmsY = (1 << mZoom) - 1 - mTmsY;

        std::stringstream strStream;

        for (int32_t i = mZoom; i > 0; i--) {
            auto digit = 0;
            auto maks = 1 << (i - 1);

            if ((tmsX & maks) != 0) {
                digit += 1;
            }

            if ((tmsY & maks) != 0) {
                digit += 2;
            }

            strStream << digit;
        }

        return strStream.str();
    }

    uint32_t TileTmz::Zoom() const {
        return mZoom;
    }

    int32_t TileTmz::TmsX() const {
        return mTmsX;
    }

    int32_t TileTmz::TmsY() const {
        return mTmsY;
    }

}