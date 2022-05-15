#ifndef SDLSPRITESAMPLE_H_
#define SDLSPRITESAMPLE_H_

#include <memory>

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "basic_engine/sprite.h"

struct SDL_Renderer;

class SdlSpriteSample 
	: public ClientGraphicApplication, public KeyboardEventListener {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;

	std::unique_ptr<basic_engine::Sprite> mSampleSprite;
	
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif // !SDLSPRITESAMPLE_H_

