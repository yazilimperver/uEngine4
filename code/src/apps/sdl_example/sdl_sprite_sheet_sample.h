#ifndef SDLSPRITESHEETSAMPLE_H_
#define SDLSPRITESHEETSAMPLE_H_

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "sprite_sheet/sprite_sheet.h"

class SdlSpriteSheetSample
	: public ClientGraphicApplication, public KeyboardEventListener {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	void CheckAnimation();
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;

	//! Movement flags
	bool mTopMovementInitiated;
	bool mBottomMovementInitiated;
	bool mLeftMovementInitiated;
	bool mRightMovementInitiated;

	std::unique_ptr<basic_engine::SpriteSheet> mSampleSpriteSheet;

	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif // !SDLSPRITESHEETSAMPLE_H_

