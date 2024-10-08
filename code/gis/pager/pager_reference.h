/**
 * @file pager_reference.h.
 * @date 21.08.2022
 * @author Yazilimperver
 * @brief  Mevcut pafta  yukleyici tarafından kullanılacak olan referans pafta bilgileri
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
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

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
