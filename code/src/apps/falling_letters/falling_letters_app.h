/**
 * @file falling_letters_app.h.
 * @date 8.11.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef FALLING_LETTERS_APP_H
#define FALLING_LETTERS_APP_H

#include "application_base/keyboard_event_listener.h"

#include "sdl_application/sdl_application.h"

#include "falling_letters_graphics_app.h"

class FallingLettersApp : public SdlApplication, public KeyboardEventListener {
public:
	FallingLettersApp();

	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
private:
	std::shared_ptr<FallingLettersGraphicApp> mApp{ std::make_shared<FallingLettersGraphicApp>() };
};

#endif // !FALLING_LETTERS_APP_H
