/**
 * @file sprite.h.
 * @date 12.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "SDL.h"

#include "sprite_parameter.h"
#include "transformation.h"
#include "rectangle.h"
#include "asset/asset.h"

namespace basic_engine {
	class SdlTextureAsset;

	class Sprite {
	public:
		Sprite(const SpriteParameter& params);
		void Update(double tickTimeInMsec);
		void Display(SDL_Renderer* renderer) const;
		Transformation& Transform();
	protected:
		Transformation mTransform;
		SDL_Rect mBoundary;
		SdlTextureAsset* mTexture;
		SDL_RendererFlip mFlip;
	};
}
#endif // !GAMEOBJECT
