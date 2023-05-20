#define SDL_MAIN_HANDLED

#include "sdl_application/sdl_application.h"
#include "gl_example.h"

int main() {
	GLExample sdlApp;

	sdlApp.Start();
	 
	return 0;
}