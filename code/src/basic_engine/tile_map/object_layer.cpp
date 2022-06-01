#include "object_layer.h"

#include "SDL.h"
#include "SDL_image.h"

#include "tileson.hpp"

#include "basic_engine/game.h"

#include "sdl_asset/sdl_texture_asset.h"

namespace basic_engine {

	Vector2f GetTileOffset(int tileId, tson::Map* map, tson::Tileset* tileset) {
		int32_t firstId = tileset->getFirstgid(); //First tile id of the tileset
		int32_t columns = tileset->getColumns(); //For the demo map it is 8.
		int32_t rows = tileset->getTileCount() / columns;
		int32_t lastId = (tileset->getFirstgid() + tileset->getTileCount()) - 1;

		//With this, I know that it's related to the tileset above (though I only have one tileset)
		if (tileId >= firstId && tileId <= lastId) {
			int32_t baseTilePosition = (tileId - firstId);

			int32_t tileModX = (baseTilePosition % columns);
			int32_t currentRow = (baseTilePosition / columns);
			int32_t offsetX = (tileModX != 0) ? ((tileModX)*map->getTileSize().x) : (0 * map->getTileSize().x);
			int32_t offsetY = (currentRow < rows - 1) ? (currentRow * map->getTileSize().y) : ((rows - 1) * map->getTileSize().y);
			return Vector2f((float)offsetX, (float)offsetY);
		}

		return Vector2f{ 0.f, 0.f };
	}

	ObjectLayer::ObjectLayer(std::string_view rootPath, tson::Layer& layer) {
		auto* map = layer.getMap();
		for (auto& obj : layer.getObjects()) {
			switch (obj.getObjectType()) {
			case tson::ObjectType::Object: {
				tson::Tileset* tileset = layer.getMap()->getTilesetByGid(obj.getGid());
				Vector2f offset = GetTileOffset(obj.getGid(), map, tileset);

				// Tiled konum olarak sol alti veriyor, sdl icin sol ustu veriyoz
				// Bunu resmin ortasina gelecek sekilde yapabiliriz
				Vector2f position = { obj.getPosition().x, obj.getPosition().y - obj.getSize().y };

				Rectangle<int32_t> textureRect{ static_cast<int32_t>(offset.x), static_cast<int32_t>(offset.y), obj.getSize().x, obj.getSize().y };

				auto imagePath = rootPath.data() + tileset->getImage().string();
				auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, imagePath, layer.getName());

				if (textHandle.has_value()) {
					auto loadedTexture = dynamic_cast<SdlTextureAsset*>(Game::AssetService().GetAsset(textHandle.value()));
					auto sprite = std::make_unique<Sprite>(loadedTexture,
						textureRect,
						SDL_FLIP_NONE);

					sprite->Move(position.x, position.y);

					mObjectSprites.emplace_back(std::move(sprite));
				}
			}

			case tson::ObjectType::Ellipse:
				break;

			case tson::ObjectType::Rectangle:
				break;

			case tson::ObjectType::Point:
				break;

			case tson::ObjectType::Polygon:
				break;

			case tson::ObjectType::Polyline:
				//Not used by the demo map, but you could use the properties of obj for a sf::ConvexShape
				break;

			case tson::ObjectType::Text:
				/*			m_demoText.setFont(m_font);
							m_demoText.setPosition({ (float)obj.getPosition().x, (float)obj.getPosition().y });
							m_demoText.setString(obj.getText().text);
							m_demoText.setCharacterSize(32); //It is 16, but makes it double for a "sharp text hack"
							m_demoText.setScale(0.5f, 0.5f); //Half scale for making a sharp text.
							m_window.draw(m_demoText);*/
				break;

			case tson::ObjectType::Template:
				break;

			default:
				break;
			}
		}
	}

	void ObjectLayer::Update(double deltaTimeInMsec) {
		for (auto& tile : mObjectSprites) {
			tile->Update(deltaTimeInMsec);
		}
	}

	void ObjectLayer::Display(SDL_Renderer* renderer) const {
		for (auto& tile : mObjectSprites) {
			tile->Display(renderer);
		}
	}
}