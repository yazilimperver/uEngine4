#include "tile_map.h"

#include "image_layer.h"
#include "tile_layer.h"
#include "object_layer.h"

#include "basic_engine/game.h"

#include "sdl_asset/sdl_texture_asset.h"

#include "spdlog/spdlog.h"

namespace basic_engine {

    std::string GetLayerTypeString(tson::LayerType type);

    TileMap::TileMap(std::string_view tileMapFile)
        :mTileMapFile{ tileMapFile.data() } {

    }

	bool TileMap::Initialize() {
		std::vector<tson::Layer> mLayers;

        tson::Tileson t;
		// dosya bazýnda sýkýþtýrýlmýþ olan haritalar için kullanýlabilir
        //mTileMap = t.parse(mTileMapFile, std::make_unique<tson::Lzma>());
        mTileMap = t.parse(mTileMapFile);
        
        if (mTileMap->getStatus() == tson::ParseStatus::OK) {
            spdlog::info("Tilemap file parse succeded! File name: {}", mTileMapFile);

			// Onden tilesetleri ve geri planlari yukleyebiliriz
			for (auto& tileset : mTileMap->getTilesets()) {
				auto path = GetPath(tileset.getImage().string());
				auto textHandle = Game::AssetService().LoadAsset(SdlTextureAsset::SdlTextureTypeStr, path, tileset.getName());

				if (!textHandle.has_value()) {
					spdlog::info("Tilemap image file load error! Tilemap Name: {} File name: {}", tileset.getName(), path);
				}
			}

            tson::Colori bgColor = mTileMap->getBackgroundColor();
            mBackgroundColor = { bgColor.r, bgColor.g, bgColor.b, bgColor.a };
            
            // katmanlara bakalim
			mLayers = mTileMap->getLayers();
            for (auto& layer : mLayers) {
                spdlog::info("Layer Name: {} - Layer Type: {}", layer.getName(), GetLayerTypeString(layer.getType()));

                switch (layer.getType()) {
                case tson::LayerType::TileLayer:
					InitializeTileLayer(layer);
                    break;

                case tson::LayerType::ObjectGroup:
					InitializeObjectLayer(layer);
                    break;

                case tson::LayerType::ImageLayer:
					InitializeImageLayer(layer);
                    break;

                case tson::LayerType::Group:
                    break;

                default:
                    break;
                }
            }
        }
        else {
            spdlog::info("Tilemap files parse failed! File name: {}", mTileMapFile);
        }

        return false;
    }

	void TileMap::InitializeObjectLayer(tson::Layer& layer)	{
		mDisplayLayers.emplace_back(std::make_unique<ObjectLayer>(mRootPath, layer));
	}

	void TileMap::InitializeTileLayer(tson::Layer& layer) {
		mDisplayLayers.emplace_back(std::make_unique<TileLayer>(mRootPath, layer));
	}

	void TileMap::InitializeImageLayer(tson::Layer& layer) {
		mDisplayLayers.emplace_back(std::make_unique<ImageLayer>(mRootPath, layer));
	}

	void TileMap::Update(double deltaTimeInMsec) 	{
		for (const auto& layer : mDisplayLayers) {
			layer->Update(deltaTimeInMsec);
		}
	}

	void TileMap::Display(SDL_Renderer* renderer) const	{
		for (const auto& layer : mDisplayLayers) {
			layer->Display(renderer);
		}
	}

	std::string TileMap::GetPath(std::string_view assetPath) {
		return mRootPath + std::string(assetPath.data());
	}

    std::string GetLayerTypeString(tson::LayerType type) {
        switch (type) {
        case tson::LayerType::TileLayer:
            return "Tile Layer";

        case tson::LayerType::ObjectGroup:
            return "Object Group";

        case tson::LayerType::ImageLayer:
            return "Image Layer";

        case tson::LayerType::Group:
            return "Group Layer";

        default:
            return "Undefined";
        }
    }
}

//#include "tileson.hpp"

//Tileson uses an alias fs for std::filesystem.
/*
int main()
tson::Tileson t;
std::unique_ptr<tson::Map> map = t.parse(tson_files::_ULTIMATE_TEST_JSON, tson_files::_ULTIMATE_TEST_JSON_SIZE);

if (map->getStatus() == tson::ParseStatus::OK)
{
    //Get color as an rgba color object
    tson::Colori bgColor = map->getBackgroundColor(); //RGBA with 0-255 on each channel

    //This color can be compared with Tiled hex string
    if (bgColor == "#ffaa07")
        printf("Cool!");

    //Or you can compare them with other colors
    tson::Colori otherColor{ 255, 170, 7, 255 };
    if (bgColor == otherColor)
        printf("This works, too!");

    //You can also get the color as float, transforming values if they are already in their int form, from max 255 to 1.f
    tson::Colorf bgColorFloat = bgColor.asFloat();

    //Or the other way around
    tson::Colori newBg = bgColorFloat.asInt();

    //You can loop through every container of objects
    for (auto& layer : map->getLayers())
    {
        if (layer.getType() == tson::LayerType::ObjectGroup)
        {
            for (auto& obj : layer.getObjects())
            {
                //Just iterate through all the objects
            }
            //Or use these queries:

            //Gets the first object it finds with the name specified
            tson::Object* player = layer.firstObj("player"); //Does not exist in demo map->..

            //Gets all objects with a matching name
            std::vector<tson::Object> enemies = layer.getObjectsByName("goomba"); //But we got two of those

            //Gets all objects of a specific type
            std::vector<tson::Object> objects = layer.getObjectsByType(tson::ObjectType::Object);

            //Gets an unique object by its name.
            tson::Object* uniqueObj = layer.getObj(2);
        }
    }

    //Or get a specific object if you know its name (or id)
    tson::Layer* layer = map->getLayer("Main Layer");
    tson::Tileset* tileset = map->getTileset("demo-tileset");
    tson::Tile* tile = tileset->getTile(1); //Tileson tile-IDs starts with 1, to be consistent
    // with IDs in data lists. This is in other words the
    //first tile.

    //For tile layers, you can get the tiles presented as a 2D map by calling getTileData()
    //Using x and y positions in tile units.
    if (layer->getType() == tson::LayerType::TileLayer)
    {
        //When the map is of a fixed size, you can get the tiles like this
        if (!map->isInfinite())
        {
            std::map<std::tuple<int, int>, tson::Tile*> tileData = layer->getTileData();

            //Unsafe way to get a tile
            tson::Tile* invalidTile = tileData[{0, 4}]; // x:0,  y:4  - There is no tile here, so this will be nullptr.
                                                               // Be careful with this, as it expands the map with an ID of {0,4} pointing
                                                               // to a nullptr...

            //Individual tiles should be retrieved by calling the safe version:
            tson::Tile* safeInvalid = layer->getTileData(0, 5); //Another non-existent tile, but with safety check.
                                                                     //Will not expand the map with a nullptr

            tson::Tile* tile1 = layer->getTileData(4, 4);       //x:4,  y:4  - Points to tile with ID 1 (Tiled internal ID: 0)
            tson::Tile* tile2 = layer->getTileData(5, 4);       //x:5,  y:4  - Points to tile with ID 3 (Tiled internal ID: 2)
            tson::Tile* tile3 = layer->getTileData(8, 14);      //x:8,  y:14 - Points to tile with ID 2 (Tiled internal ID: 1)
            tson::Tile* tile4 = layer->getTileData(17, 5);      //x:17, y:5  - Points to tile with ID 5 (Tiled internal ID: 4)

            //New in v1.2.0
            //You can now get tiles with positions and drawing rect via tson::TileObject
            //Drawing rects are also accessible through tson::Tile.
            tson::TileObject* tileobj1 = layer->getTileObject(4, 4);
            tson::Vector2f position = tileobj1->getPosition();
            tson::Rect drawingRect = tileobj1->getDrawingRect();

            //You can of course also loop through every tile!
            for (const auto& [id, tile] : tileData)
            {
                //Must check for nullptr, due to how we got the first invalid tile (pos: 0, 4)
                //Would be unnecessary otherwise.
                if (tile != nullptr)
                    int tileId = tile->getId(); //A bit verbose, as this is the same as id from the key, but you get the idea.
            }
        }
    }

    //If an object supports properties, you can easily get a property value by calling get<T>() or the property itself with getProp()
    int myInt = layer->get<int>("my_int");
    float myFloat = layer->get<float>("my_float");
    bool myBool = layer->get<bool>("my_bool");
    std::string myString = layer->get<std::string>("my_string");
    tson::Colori myColor = layer->get<tson::Colori>("my_color");

    fs::path file = layer->get<fs::path>("my_file");

    tson::Property* prop = layer->getProp("my_property");
}
else //Error occured
{
    std::cout << map->getStatusMessage();
}

return 0;
}*/

/* SDL Example
#include <stdio.h>
#include <tmx.h>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_image.h>

#define DISPLAY_H 600
#define DISPLAY_W 800

static SDL_Renderer *ren = NULL;

void* SDL_tex_loader(const char *path) {
	return IMG_LoadTexture(ren, path);
}

void set_color(int color) {
	tmx_col_bytes col = tmx_col_to_bytes(color);
	SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);
}

void draw_polyline(double **points, double x, double y, int pointsc) {
	int i;
	for (i=1; i<pointsc; i++) {
		SDL_RenderDrawLine(ren, x+points[i-1][0], y+points[i-1][1], x+points[i][0], y+points[i][1]);
	}
}

void draw_polygon(double **points, double x, double y, int pointsc) {
	draw_polyline(points, x, y, pointsc);
	if (pointsc > 2) {
		SDL_RenderDrawLine(ren, x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
	}
}

void draw_objects(tmx_object_group *objgr) {
	SDL_Rect rect;
	set_color(objgr->color);
	tmx_object *head = objgr->head;
	while (head) {
		if (head->visible) {
			if (head->obj_type == OT_SQUARE) {
				rect.x =     head->x;  rect.y =      head->y;
				rect.w = head->width;  rect.h = head->height;
				SDL_RenderDrawRect(ren, &rect);
			}
			else if (head->obj_type  == OT_POLYGON) {
				draw_polygon(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
			}
			else if (head->obj_type == OT_POLYLINE) {
				draw_polyline(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
			}
			else if (head->obj_type == OT_ELLIPSE) {
			}
		}
		head = head->next;
	}
}

void draw_tile(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
	unsigned int dx, unsigned int dy, float opacity, unsigned int flags) {
	SDL_Rect src_rect, dest_rect;
	src_rect.x = sx;
	src_rect.y = sy;
	src_rect.w = dest_rect.w = sw;
	src_rect.h = dest_rect.h = sh;
	dest_rect.x = dx;
	dest_rect.y = dy;
	SDL_RenderCopy(ren, (SDL_Texture*)image, &src_rect, &dest_rect);
}

void draw_layer(tmx_map* map, tmx_layer* layer) {
	unsigned long i, j;
	unsigned int gid, x, y, w, h, flags;
	float op;
	tmx_tileset* ts;
	tmx_image* im;
	void* image;
	op = layer->opacity;
	for (i = 0; i < map->height; i++) {
		for (j = 0; j < map->width; j++) {
			gid = (layer->content.gids[(i * map->width) + j]) & TMX_FLIP_BITS_REMOVAL;
			if (map->tiles[gid] != NULL) {
				ts = map->tiles[gid]->tileset;
				im = map->tiles[gid]->image;
				x = map->tiles[gid]->ul_x;
				y = map->tiles[gid]->ul_y;
				w = ts->tile_width;
				h = ts->tile_height;
				if (im) {
					image = im->resource_image;
				}
				else {
					image = ts->image->resource_image;
				}
				flags = (layer->content.gids[(i * map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
				draw_tile(image, x, y, w, h, j * ts->tile_width, i * ts->tile_height, op, flags);
			}
		}
	}
}

void draw_image_layer(tmx_image* image) {
	SDL_Rect dim;
	dim.x = dim.y = 0;

	SDL_Texture* texture = (SDL_Texture*)image->resource_image; // Texture loaded by libTMX
	SDL_QueryTexture(texture, NULL, NULL, &(dim.w), &(dim.h));
	SDL_RenderCopy(ren, texture, NULL, &dim);
}

void draw_all_layers(tmx_map* map, tmx_layer* layers) {
	while (layers) {
		if (layers->visible) {

			if (layers->type == L_GROUP) {
				draw_all_layers(map, layers->content.group_head);
			}
			else if (layers->type == L_OBJGR) {
				draw_objects(layers->content.objgr);
			}
			else if (layers->type == L_IMAGE) {
				draw_image_layer(layers->content.image);
			}
			else if (layers->type == L_LAYER) {
				draw_layer(map, layers);
			}
		}
		layers = layers->next;
	}
}

void render_map(tmx_map* map) {
	set_color(map->backgroundcolor);
	SDL_RenderClear(ren);
	draw_all_layers(map, map->ly_head);
}

Uint32 timer_func(Uint32 interval, void* param) {
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return(interval);
}

int main(int argc, char** argv) {
	SDL_Window* win;
	SDL_Event ev;
	SDL_TimerID timer_id;

	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
		fputs(SDL_GetError(), stderr);
		return 1;
	}

	if (!(win = SDL_CreateWindow("SDL2 example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN))) {
		fputs(SDL_GetError(), stderr);
		return 1;
	}

	if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		fputs(SDL_GetError(), stderr);
		return 1;
	}

	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);

	timer_id = SDL_AddTimer(30, timer_func, NULL);

	tmx_img_load_func = SDL_tex_loader;
	tmx_img_free_func = (void (*)(void*))SDL_DestroyTexture;

	tmx_map* map = tmx_load(argv[1]);
	if (!map) {
		tmx_perror("Cannot load map");
		return 1;
	}

	while (SDL_WaitEvent(&ev)) {

		if (ev.type == SDL_QUIT) break;

		render_map(map);
		SDL_RenderPresent(ren);
	}

	tmx_map_free(map);

	SDL_RemoveTimer(timer_id);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
*/