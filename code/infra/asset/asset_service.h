/**
 * @file asset_service.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief Uygulama tarafindan doku, ses vb. `asset` lerin gerceklemesi beklenen servis arayuzudur.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ASSET_SERVICE
#define ASSET_SERVICE

#include <any>
#include <memory>
#include <optional>
#include <string_view>

#include "asset.h"
#include "asset_loader.h"

namespace infra {
	class AssetService {
	public:
		virtual void RegisterLoader(std::shared_ptr<AssetLoader>) = 0;
        virtual std::optional<AssetLoaderHandle> LoaderHandle(std::string_view loaderName) = 0;
        virtual std::optional<AssetHandle> LoadAsset(AssetLoaderHandle name, std::string_view path, std::string_view label) = 0;
		virtual std::optional<AssetHandle> LoadAsset(AssetLoaderName type, std::string_view path, std::string_view label) = 0;
		virtual void DisposeAsset(AssetHandle) = 0;
        virtual std::shared_ptr<Asset> SharedAsset(AssetHandle) = 0;
		virtual Asset* GetAsset(AssetHandle) = 0;
		virtual Asset* GetAsset(std::string_view) = 0;
	};
}

#endif // ASSET_SERVICE

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
