#include "SDL.h"
#include "SDL_image.h"

#include "tile.h"

Tile::Tile(int x, int y, int zoom): zoom(zoom), x(x), y(y), surface(NULL), state(EMPTY){};
bool Tile::loaded(){
	return !!surface;
}
void Tile::queue(){
	state = QUEUED;
}
void Tile::load(char *memory, int size){
	SDL_Surface *img = IMG_Load_RW(SDL_RWFromMem(memory, size), 1);
	surface = img;
	//surface = SDL_DisplayFormat(img);
	//SDL_FreeSurface(img);
	state = LOADED;
}
std::string Tile::url(){
	char url[4096];
	//snprintf(url, sizeof url, "http://a.tile.openstreetmap.org/%i/%i/%i.png", zoom, x, y);
	//snprintf(url, sizeof url, "http://a.tile.stamen.com/toner/%i/%i/%i.png", zoom, x, y);
	snprintf(url, sizeof url, "http://mts0.google.com/vt/hl=en&src=api&x=%i&s=&y=%i&z=%i", x, y, zoom);
	//snprintf(url, sizeof url, "http://a.www.toolserver.org/tiles/bw-mapnik/%i/%i/%i.png", zoom, x, y);
	return std::string(url);
}
void Tile::render(SDL_Surface *screen, int offsetx, int offsety){
	SDL_Rect dest = {x * TILESIZE - offsetx, y * TILESIZE - offsety, TILESIZE, TILESIZE};
	while(dest.x <= -TILESIZE){
		dest.x += (1 << zoom) * TILESIZE;
	}
	if(surface){
		//printf("render: (%i, %i, %i) => (%i, %i)\n", x, y, zoom, dest.x, dest.y);
		SDL_BlitSurface(surface, NULL, screen, &dest);
	}else{
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 255, 255, 255));
	}
}
