#include "tile_layer.h"

#include "SDL.h"
#include "SDL_image.h"

#include "tileson.hpp"

#include "sdl_asset/sdl_texture_asset.h"
#include "spdlog/spdlog.h"

#include "basic_engine/game.h"

namespace basic_engine {
	inline auto GetRectangle(const tson::Rect& rect) {
		return infra::Rectangle<int32_t>{rect.x, rect.y, rect.width, rect.height };
	}

	TileLayer::TileLayer(std::string_view rootPath, tson::Layer& layer) {
		spdlog::info("This tile layer has {} tile objects!", layer.getTileObjects().size());
		
		tson::Tileset* tileset{ nullptr };
		tson::Vector2f position;
		for (auto& [pos, tileObject] : layer.getTileObjects()) {
			auto tile = tileObject.getTile();
			tileset = tile->getTileset();
			
			// Ortak verileri okuyalim
			position = tileObject.getPosition();

			position.x += layer.getOffset().x;
			position.y += layer.getOffset().y;

			auto tileSetPath = std::string(rootPath.data()) + tileset->getImage().string();
			auto textHandle = Game::GetAssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, tileSetPath, tileset->getName());
			
			float rotation{ 0.0f };
			Vector2f scale{ 1.0F, 1.0F };

			if (tileObject.getTile()->hasFlipFlags(tson::TileFlipFlags::Horizontally))
				scale.x = -scale.x;
			if (tileObject.getTile()->hasFlipFlags(tson::TileFlipFlags::Vertically))
				scale.y = -scale.y;
			if (tileObject.getTile()->hasFlipFlags(tson::TileFlipFlags::Diagonally))
				rotation += 90.f;

			if (textHandle.has_value()) {
				auto texture = dynamic_cast<SdlTextureAsset*>(Game::GetAssetService().GetAsset(textHandle.value()));
				bool hasAnimation = tile->getAnimation().any();
				
				if (!hasAnimation) {
					mNonAnimatedSprites.emplace_back(std::make_unique<Sprite>(texture, GetRectangle(tileObject.getDrawingRect()), SDL_FLIP_NONE));
					mNonAnimatedSprites[mNonAnimatedSprites.size() - 1]->SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
					mNonAnimatedSprites[mNonAnimatedSprites.size() - 1]->SetScale(scale);
					mNonAnimatedSprites[mNonAnimatedSprites.size() - 1]->Rotate(rotation);
				}
				else {
					auto animation = tile->getAnimation();

					spdlog::info("Animated tile! Tile ID: {} Frame Count: {}", tile->getId(), animation.size());

					AnimatedTile newTile;

					for (auto& frame : animation.getFrames()){
						tson::Tile* animatedTile = tileset->getTile(frame.getTileId());

						newTile.FrameSprites.emplace_back(std::make_unique<Sprite>(texture, GetRectangle(animatedTile->getDrawingRect()), SDL_FLIP_NONE));
						newTile.FrameSprites[newTile.FrameSprites.size() - 1]->SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
						newTile.FrameSprites[newTile.FrameSprites.size() - 1]->SetScale(scale);
						newTile.FrameSprites[newTile.FrameSprites.size() - 1]->Rotate(rotation);
						newTile.FrameTimesInMsec.emplace_back(frame.getDuration());
					}

					mAnimatedSprites.emplace_back(std::move(newTile));
				}
			}
			else {
				spdlog::info("Error in loading tile asset! Name: {} Path: {}", tileset->getName(), tileSetPath);
			}
		}

	}
	
	void TileLayer::CheckTileAnimation(AnimatedTile& animatedTile, double deltaTimeInMsec) {
		animatedTile.ElapsedTime += deltaTimeInMsec;

		auto& currentFrameTime = animatedTile.FrameTimesInMsec[animatedTile.ActiveFrame];

		if (animatedTile.ElapsedTime > currentFrameTime) {
			animatedTile.ElapsedTime = 0;
			animatedTile.ActiveFrame = (animatedTile.ActiveFrame + 1) % animatedTile.FrameSprites.size();
		}
	}

	void TileLayer::Update(double deltaTimeInMsec) {
		for (auto& tile : mNonAnimatedSprites) {
			tile->Update(deltaTimeInMsec);
		}

		for (auto& animatedTile : mAnimatedSprites) {
			CheckTileAnimation(animatedTile, deltaTimeInMsec);

			auto& currentSprite = animatedTile.FrameSprites[animatedTile.ActiveFrame];
			currentSprite->Update(deltaTimeInMsec);
		}
	}

	void TileLayer::Display(SDL_Renderer* renderer) const {
		for (const auto& tile : mNonAnimatedSprites) {
			tile->Display(renderer);
		}
		
		for (const auto& animatedTile : mAnimatedSprites) {
			animatedTile.FrameSprites[animatedTile.ActiveFrame]->Display(renderer);
		}
	}
}