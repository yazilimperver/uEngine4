/**
 * @file asset_loader.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief  Genel olarak veri yukleme icin kullanilabilecek servislerin belirten arayuz
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef ASSET_LOADER
#define ASSET_LOADER

#include <string_view>
#include <memory>

#include "asset.h"

namespace basic_engine {
	class AssetLoader {
	public:
		virtual std::unique_ptr<Asset> Load(std::string_view path, std::string_view label) = 0;

		/* @brief Sadece ilgili asset'e dair elden cikarma islerini yapacagiz. Sahipligi aktarmadigimiz icin pass by ref!
		 *		  http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
		 */
		virtual void Dispose(std::unique_ptr<Asset>&) = 0;
		virtual AssetType Type() = 0;
	};
}

#endif

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
