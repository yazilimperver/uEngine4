/**
 * @file sdl_sprite_sheet_sample.h.
 * @date 10.08.2022
 * @author Yazilimperver
 * @brief SpriteSheet nesnesine iliskin ornek bir kullanim gostermektedir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
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

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
