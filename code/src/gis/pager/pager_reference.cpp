#include "pager_reference.h"

namespace gis {
    bool operator== (const PagerReference& left, const PagerReference& right) {
        return (left.Position == right.Position &&
            left.ZoomLevel == right.ZoomLevel &&
            left.TileInfo == right.TileInfo);
    }

    bool operator!= (const PagerReference& left, const PagerReference& right) {
        return (left.Position != right.Position ||
            left.ZoomLevel != right.ZoomLevel ||
            left.TileInfo != right.TileInfo);
    }
}