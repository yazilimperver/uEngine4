#include "sdl_application/sdl_application.h"
#include "primitive_sample.h"

int main() {
	/* Empty SDL app
	SdlApplication sldApp;
	sldApp.Start();*/

	PrimitiveSample sdlApp;
	sdlApp.Start();

	return 0;
}