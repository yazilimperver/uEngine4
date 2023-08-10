/**
 * @file asset_info.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief  Bu motor icin kullanilacak olan `asset` lere iliskin temel bilgileri tutan veri yapisi
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ASSETINFO
#define ASSETINFO

#include <string>

#include "asset_common.h"

namespace infra {

	/** @brief Asset tiplerini jenerik tutmak ve ihtiyacimizi da gordugu icin metin olarak tutabiliriz */
	using AssetLoaderName = std::string;

	struct AssetInfo {
		enum class Status {
			NotActive,
			LoadRequested,
			LoadInProgress,
			LoadSuccessful,
			LoadFailed,
			Active
		};

        enum class AssetType : int32_t {
            None = -1,
            Texture,
            Shader,
            Configuration,
            Plugin,
            Model3d,
            Audio,
            Count
        };

		AssetHandle mHandle{ 0 };
		Status mStatus{ Status::NotActive };
		std::string mLabel{ "" };
		std::string mPath{ "" };
        uint32_t mSize{ 0 };
		AssetLoaderHandle   mLoaderHandle{ -1 };
        AssetType Asset_Type{ AssetType::None };
	};

	/** @brief Asset'lerin mevcut durumu */
	using AssetStatus = AssetInfo::Status;
}

#endif // !ASSETINFO

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
