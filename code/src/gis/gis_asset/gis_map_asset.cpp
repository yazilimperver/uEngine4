#include "gis_map_asset.h"

#include "SDL.h"

namespace gis_asset {
	GisMapAsset::GisMapAsset(SDL_Texture* texture, int32_t width, int32_t height){
		mTexture = texture;
		mWidth = width;
		mHeight = height;
	}

	SDL_Texture* GisMapAsset::Texture() const {
		return mTexture;
	}

	const infra::AssetInfo& GisMapAsset::Info() const {
		return mInfo;
	}

	infra::AssetInfo& GisMapAsset::InfoRef() {
		return mInfo;
	}

	int32_t GisMapAsset::Width() const {
		return mWidth;
	}

	int32_t GisMapAsset::Height() const {
		return mHeight;
	}
    bool GisMapAsset::IsValid() const {
        return mTexture != nullptr;
    }
}