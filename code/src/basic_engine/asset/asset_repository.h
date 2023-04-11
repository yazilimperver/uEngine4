/**
 * @file asset_repository.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief Motor icerisine kayitlanmis olan `asset` yukleyicileri, `asset` yukleme ve benzeri `asset` servislerini gercekleyen temel siniftir.
 *		  Su an icin SDL bagimliligimiz mevcut
 *		  TODO: Thread safety :)
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ASSET_REPOSITORY
#define ASSET_REPOSITORY

#include <unordered_map>

#include "asset_service.h"

struct SDL_Renderer;

namespace basic_engine {
	class AssetRepository 
		: public AssetService {
	public:
		virtual void RegisterLoader(std::unique_ptr<AssetLoader>) override;
		virtual std::optional<AssetHandle> LoadAsset(AssetType, std::string_view path, std::string_view label) override;
		virtual void DisposeAsset(AssetHandle) override;
		virtual Asset* GetAsset(AssetHandle) override;
		virtual Asset* GetAsset(std::string_view label) override;
		void AssignRenderer(SDL_Renderer* renderer);
	protected:
		SDL_Renderer* mRenderer{nullptr};
		std::unordered_map<AssetHandle, std::unique_ptr<Asset>> mAssetPool;
		std::unordered_map<std::string, AssetHandle> mLoadedAssets;
		std::unordered_map<std::string, AssetHandle> mLabeledAssets;
		std::unordered_map<AssetType, std::unique_ptr<AssetLoader>> mAssetLoaders;
	};
}

#endif // !ASSET_REPOSITORY
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
