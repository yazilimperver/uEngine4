#ifndef PAGER_REFERENCE_H
#define PAGER_REFERENCE_H

#include "core_gis/common.h"

#include "tile_id.h"

namespace gis {

    struct PagerReference {
        PointInPixels Position{ 0, 0 };
        uint32_t ZoomLevel{ 0 };
        TileId TileInfo;

        friend bool operator== (const PagerReference& l, const PagerReference& r);
        friend bool operator!= (const PagerReference& l, const PagerReference& r);
    };
}

#endif // !PAGER_REFERENCE_H

