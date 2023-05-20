/**
 * @file sdl_texture_loader.h.
 * @date 9.05.2022
 * @author Yazilimperver
 * @brief SDL destekli dokulari SDL_Image kutuphanesi kullanarak yuklemek icin kullanilabilecek siniftir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLTEXTURELOADER
#define SDLTEXTURELOADER

#include "asset/asset_loader.h"

struct SDL_Renderer;

namespace basic_engine {
	class SdlTextureLoader : public AssetLoader {
	public:
		void AssignRenderer(SDL_Renderer* renderer);
		virtual std::unique_ptr<Asset> Load(std::string_view path, std::string_view label) override;
		virtual void Dispose(std::unique_ptr<Asset>) override;
		virtual AssetType Type() override;
	protected:
		SDL_Renderer* mRenderer{ nullptr };
	};
}

#endif // !SDLTEXTURELOADER

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
