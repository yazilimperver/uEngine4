#include "sdl_input_sample.h"

#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"

#include "spdlog/spdlog.h"

void SdlInputSample::Initialize(SdlApplication& sdlApplication) {
	static bool isInitialized{ false };

	if (false == isInitialized)	{
		mRenderer = sdlApplication.GetSdlRenderer();
		mParameters = sdlApplication.GetWindowParametrs();

		sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

		isInitialized = true;
	}
}

void SdlInputSample::Update(double tickTimeInMsec) {
}

void SdlInputSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	//Render red filled quad
	SDL_Rect fillRect = { mCenter.x +  static_cast<int32_t>(mParameters.Width) / 4, mCenter.y + static_cast<int32_t>(mParameters.Height) / 4, static_cast<int32_t>(mParameters.Width) / 2, static_cast<int32_t>(mParameters.Height) / 2 };
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(mRenderer, &fillRect);

	//Render green outlined quad
	SDL_Rect outlineRect = { mCenter.x + static_cast<int32_t>(mParameters.Width) / 6, mCenter.y + static_cast<int32_t>(mParameters.Height) / 6, static_cast<int32_t>(mParameters.Width) * 2 / 3, static_cast<int32_t>(mParameters.Height) * 2 / 3 };
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(mRenderer, &outlineRect);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width), static_cast<int32_t>(mParameters.Height) / 2);

	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < static_cast<int32_t>(mParameters.Height); i += 4) {
		SDL_RenderDrawPoint(mRenderer, static_cast<int32_t>(mParameters.Width) / 2, i);
	};
}

void SdlInputSample::Finalize() {
}

void SdlInputSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {

    if (InputActions::PressAction == action) {
        if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			mCenter.y -= 1;
        }
        else if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mCenter.y += 1;
        }
        else if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mCenter.x += 1;
        }
        else if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mCenter.x -= 1;        }
    }
}
