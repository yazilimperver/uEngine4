/**
 * @file sdl_texture_asset.h.
 * @date 9.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLTEXTUREASSET
#define SDLTEXTUREASSET

#include "asset/asset.h"

struct SDL_Texture;

namespace basic_engine {
	class SdlTextureAsset : public Asset {
	public:
		SdlTextureAsset();

		/** @brief Olusturulan SDL doku nesnesini aktaralim*/
		void AssignTexture(SDL_Texture* texture);
		SDL_Texture* Texture() const;

		/** @brief Veri tipi. */
		static inline const std::string SdlTextureTypeStr{ "SdlTexture" };

		/** @brief Asset bilgilerine iliskin API'ler */
		virtual const AssetInfo& Info() const override;
		AssetInfo& InfoRef();
	private:
		AssetInfo mInfo;
		SDL_Texture* mTexture{ nullptr };
	};
}

#endif // !SDLTEXTUREASSET

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