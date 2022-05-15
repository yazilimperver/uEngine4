#include "sdl_texture_asset.h"

#include "SDL.h"

namespace basic_engine {
	SdlTextureAsset::SdlTextureAsset(){ 
		mInfo.mType = SdlTextureTypeStr;
	}

	void SdlTextureAsset::AssignTexture(SDL_Texture* texture) {
		mTexture = texture;
	}

	SDL_Texture* SdlTextureAsset::Texture() const {
		return mTexture;
	}

	const AssetInfo& SdlTextureAsset::Info() const {
		return mInfo;
	}

	AssetInfo& SdlTextureAsset::InfoRef() {
		return mInfo;
	}
}