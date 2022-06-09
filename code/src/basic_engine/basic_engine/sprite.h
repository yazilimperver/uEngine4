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
		/** @brief Yukleme isi de bu sinif icerisinde yapilacak */
		Sprite(const SpriteParameter& params);

		/** @brief Zaten yuklenmis bir resmin tamamini gostermek icin kullanilacak */
		Sprite(SdlTextureAsset* textureAsset, const Vector2i& pos, SDL_RendererFlip flip);

		/** @brief Zaten yuklenmis bir resmin verilen kismi icin kullanilacak */
		Sprite(SdlTextureAsset* textureAsset, const Rectangle<int32_t>& srcRectangle, SDL_RendererFlip flip);
		void Update(double tickTimeInMsec);
		void Display(SDL_Renderer* renderer) const;
		void SetPosition(int32_t posX, int32_t posY);
		
		void Rotate(float rotate);
		void SetScale(const Vector2f& scale);
		const Transformation& Transform() const;

	protected:
		Transformation mTransform;

		/** @brief Cizim yapilacak olan hedef sinirlar */
		SDL_Rect mDestinationRect;

		/** @brief Texture icerisinden neresini kullanacagimiz */
		SDL_Rect mSourceRect;

		/** @brief Kullanilacak olan doku*/
		SdlTextureAsset* mTexture{nullptr};

		/** @brief Doku yukseklik ve genislik */
		int32_t mHeight;
		int32_t mWidth;

		/** @brief Dokuya iliskin flip bilgisi */
		SDL_RendererFlip mFlip;
	};
}
#endif // !GAMEOBJECT

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
