#include "sdl_sprite_sample.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"
#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

using namespace basic_engine;

void SdlSpriteSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	dynamic_cast<AssetRepository&>(Game::AssetService()).AssignRenderer(mRenderer);

	Game::AssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	constexpr int32_t spriteWidth{ 200 };
	constexpr int32_t spriteHeight{ 150};
	SpriteParameter params{ "sprite.png", "dragon", 
							spriteWidth, spriteHeight, 
							static_cast<float>(mParameters.Width) / 2.0f - spriteWidth / 2.0f,
							static_cast<float>(mParameters.Height) / 2.0f - spriteHeight / 2.0f,
							SDL_FLIP_NONE };

	mSampleSprite = std::make_unique<Sprite>(params);

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlSpriteSample::Update(double tickTimeInMsec) {
	mSampleSprite->Update(tickTimeInMsec);
}

void SdlSpriteSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	// Draw blue lines
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width), static_cast<int32_t>(mParameters.Height) / 2);
	SDL_RenderDrawLine(mRenderer, static_cast<int32_t>(mParameters.Width) / 2, 0, static_cast<int32_t>(mParameters.Width)/2, static_cast<int32_t>(mParameters.Height));

	mSampleSprite->Display(mRenderer);
}

void SdlSpriteSample::Finalize() {
}

void SdlSpriteSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {

	spdlog::info("Current position: <{}, {}>", mSampleSprite->Transform().Pos().x, mSampleSprite->Transform().Pos().y);
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			mSampleSprite->Transform().Move(0, -1);
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mSampleSprite->Transform().Move(0, 1);
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mSampleSprite->Transform().Move(1, 0);
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mSampleSprite->Transform().Move(-1, 0);
		}
	}
}
