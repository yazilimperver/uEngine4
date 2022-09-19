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

	dynamic_cast<AssetRepository&>(Game::GetAssetService()).AssignRenderer(mRenderer);

	Game::GetAssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	SpriteParameter params{ "sprite.png", "dragon", static_cast<int32_t>(mParameters.Width) /2, static_cast<int32_t>(mParameters.Height) / 2, SDL_FLIP_NONE};

	mSampleSprite = std::make_unique<Sprite>(params);

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlSpriteSample::Update(double tickTimeInMsec) {
	mSampleSprite->Update(tickTimeInMsec);
}

void SdlSpriteSample::Display(double tickTimeInMsec) {
	// Ekrani sil
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	// Mavi cizgileri cizelim
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
			mSampleSprite->SetPosition(mSampleSprite->Transform().Pos().x, mSampleSprite->Transform().Pos().y - 1);
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mSampleSprite->SetPosition(mSampleSprite->Transform().Pos().x, mSampleSprite->Transform().Pos().y + 1);
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mSampleSprite->SetPosition(mSampleSprite->Transform().Pos().x+1, mSampleSprite->Transform().Pos().y);
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mSampleSprite->SetPosition(mSampleSprite->Transform().Pos().x-1, mSampleSprite->Transform().Pos().y);
		}
		if (KeyboardCodes::KEY_PAGE_UP == key) {
			spdlog::info("Rotate right pressed");
			mSampleSprite->Rotate(mSampleSprite->Transform().Rotation() + 5);
		}
		if (KeyboardCodes::KEY_PAGE_DOWN == key) {
			spdlog::info("Rotate right pressed");
			mSampleSprite->Rotate(mSampleSprite->Transform().Rotation() - 5);
		}
		if (KeyboardCodes::KEY_KP_ADD == key) {
			spdlog::info("Scale up pressed");
			mSampleSprite->SetScale({ mSampleSprite->Transform().Scale().x + 0.2, mSampleSprite->Transform().Scale().y + 0.2 });
		}
		if (KeyboardCodes::KEY_KP_SUBTRACT == key) {
			spdlog::info("Scale down pressed");
			mSampleSprite->SetScale({ mSampleSprite->Transform().Scale().x - 0.2, mSampleSprite->Transform().Scale().y - 0.2 });
		}
	}
}
