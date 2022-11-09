#define SDL_MAIN_HANDLED
#include "sdl_application/sdl_application.h"
#include "falling_letters_app.h"

int main() {
	SDL_SetMainReady();
	FallingLettersApp sdlApp;
	sdlApp.Start();

	return 0;
}