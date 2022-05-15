#ifndef SPRITEPARAMETER_H
#define SPRITEPARAMETER_H

#include "SDL.h"

#include "common.h"
#include "asset/asset.h"

namespace basic_engine {
	struct SpriteParameter {
		std::string TexturePath;
		std::string TextureLabel;
		float Width;
		float Height;
		float X;
		float Y;
		SDL_RendererFlip Flip;
	};
}

#endif // !SPRITEPARAMETER_H
