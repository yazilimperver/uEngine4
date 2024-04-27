#define SDL_MAIN_HANDLED

#include "sdl_application/sdl_application.h"
#include "primitive_sample.h"

int main() {
	SDL_SetMainReady();

	PrimitiveSample sdlApp;
	sdlApp.Start();

	return 0;
}