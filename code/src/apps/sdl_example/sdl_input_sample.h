#ifndef SDLIMAGESAMPLE
#define SDLIMAGESAMPLE

#include "SDL.h"

#include "spdlog/spdlog.h"

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "sdl_application/sdl_application.h"

struct SDL_Renderer;

class SdlInputSample
	: public ClientGraphicApplication, public KeyboardEventListener {
public:
	// Inherited via ClientGraphicApplication
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;

	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;

protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;

	SDL_Point mCenter{ 0,0 };

	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif // !SDLIMAGESAMPLE

