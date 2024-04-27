/**
 * @file   gis_map_asset.h
 * @date   4/11/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_GIS_MAP_ASSET_H
#define INC_GIS_MAP_ASSET_H

#include "asset/asset.h"

struct SDL_Texture;

namespace gis_asset {
	class GisMapAsset : public infra::Asset {
	public:
		explicit GisMapAsset(SDL_Texture* texture, int32_t width, int32_t height);

		SDL_Texture* Texture() const;

		/** @brief Veri tipi. */
		static inline const std::string GisMapAssetTypeStr{ "GisMapAsset" };

		/** @brief Asset bilgilerine iliskin API'ler */
		virtual const infra::AssetInfo& Info() const override;
		infra::AssetInfo& InfoRef();

		int32_t Width() const;
		int32_t Height() const;
        virtual bool IsValid() const override;
	private:
		int32_t mWidth{ 0 };
		int32_t mHeight{ 0 };
		
		infra::AssetInfo mInfo;
		SDL_Texture* mTexture{ nullptr };
	};
}

#endif // !GISMAPASSET

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
