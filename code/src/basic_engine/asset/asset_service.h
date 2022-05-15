/**
 * @file asset_service.h.
 * @date 7.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <any>
#include <memory>
#include <optional>
#include <string_view>

#include "asset.h"
#include "asset_loader.h"

namespace basic_engine {
	class AssetService {
	public:
		virtual void RegisterLoader(std::unique_ptr<AssetLoader>) = 0;
		virtual std::optional<AssetHandle> LoadAsset(AssetType type, std::string_view path, std::string_view label) = 0;
		virtual void DisposeAsset(AssetHandle) = 0;
		virtual Asset* GetAsset(AssetHandle) = 0;
		virtual Asset* GetAsset(std::string_view) = 0;
	};
}
