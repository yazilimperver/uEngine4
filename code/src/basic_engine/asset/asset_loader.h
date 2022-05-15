/**
 * @file asset_loader.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <string_view>
#include <memory>

#include "asset.h"

struct SDL_Renderer;

namespace basic_engine {
	class AssetLoader {
	public:
		virtual std::unique_ptr<Asset> Load(SDL_Renderer* renderer, std::string_view path, std::string_view label) = 0;

		/* @brief Sadece ilgili asset'e dair elden cikarma islerini yapacagiz. Sahipligi aktarmadigimiz icin pass by ref!
		 *		  http://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
		 */
		virtual void Dispose(std::unique_ptr<Asset>&) = 0;
		virtual AssetType Type() = 0;
	};
}
