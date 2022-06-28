#ifndef MAP_VIEW_H
#define MAP_VIEW_H MAP_VIEW_H

#include "SDL.h"
#include "tile_collection.h"

class MapView{
	int width, height;
	int offsetx, offsety;
	SDL_Window *window;
	public:
		TileCollection tiles;
		int zoom;
		MapView(SDL_Window *window, int width, int height, int zoom);
		void center_coords(double lat, double lng);
		void move_by(int dx, int dy);
		void zoom_at(int x, int y);
		void zoom_in();
		void zoom_out();
		void resize(int width, int height);
		void update_bounds();
		void render();
};

#endif
