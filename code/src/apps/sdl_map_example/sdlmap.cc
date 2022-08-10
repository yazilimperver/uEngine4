/**
 * @file sdlmap.cc.
 * @date 10.08.2022
 * @author Yazilimperver
 * @brief  SDL kullanilarak harita gosterimine iliskin ornek bir uygulama. Burada curl kutuphanesi ile internet uzerinden ilgili paftalar yuklenerek gosterilmektedir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <list>
#include <set>
#include <string>
#include <vector>

#include "SDL.h"

#define TILESIZE 256

#include "sdlmap.h"
#include "tile.h"
#include "tile_collection.h"
#include "map_view.h"

void runloop(MapView &view){
	bool mousedown = false;
	bool dirty = true;
	Uint32 lastclick = 0;
	int zoomdf = 0;
	for(;;){
		SDL_Event event;
		while((dirty ? SDL_PollEvent : SDL_WaitEvent)(&event)){
			switch (event.type) {
				case SDL_MOUSEBUTTONUP:
					mousedown = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == 1){
						mousedown = true;
						if(SDL_GetTicks() - lastclick < 250){
							lastclick = 0;
							view.zoom_at(event.button.x, event.button.y);
							dirty = true;
						}
						lastclick = SDL_GetTicks();
					}
					break;
				case SDL_MOUSEWHEEL:
					zoomdf += event.wheel.y;
					if(zoomdf >= 5){
						zoomdf = 0;
						view.zoom_in();
						dirty = true;
					}else if(zoomdf <= -5){
						zoomdf = 0;
						view.zoom_out();
						dirty = true;
					}
					break;
				case SDL_MOUSEMOTION:
					if(mousedown){
						view.move_by(-event.motion.xrel, -event.motion.yrel);
						dirty = true;
					}
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							exit(0);
							break;
						case SDLK_PLUS:
						case SDLK_EQUALS:
							view.zoom_in();
							dirty = true;
							break;
						case SDLK_MINUS:
							view.zoom_out();
							dirty = true;
							break;
					}
					break;
				case SDL_WINDOWEVENT:
					switch(event.window.event){
						case SDL_WINDOWEVENT_RESIZED:
							view.resize(event.window.data1, event.window.data2);
							dirty = true;
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							dirty = true;
							break;
					}
					break;
				case SDL_QUIT:
					exit(0);
			}
		}
		if(dirty){
			view.update_bounds();
			dirty = view.tiles.work();
			view.render();
		}
	}
}



int main(int argc, char *argv[]){
	if(SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stderr, "SDL_Init failed: %s", SDL_GetError());
		exit(-1);
	}
	int width = 800, height = 600;
	int zoom = 10;
	SDL_Window *window = SDL_CreateWindow("SDLmap", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);

	MapView view(window, width, height, zoom);
	view.center_coords(40, 33);

	runloop(view);
	return 0;
}

