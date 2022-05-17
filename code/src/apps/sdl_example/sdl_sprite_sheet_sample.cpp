#include "sdl_sprite_sheet_sample.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"
#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

using namespace basic_engine;

constexpr char cSpriteSheetConfigFile[] = "SampleSpriteSheetConfig.json";

void SdlSpriteSheetSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));
	dynamic_cast<AssetRepository&>(Game::AssetService()).AssignRenderer(mRenderer);
	Game::AssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	constexpr int32_t spriteWidth{ 200 };
	constexpr int32_t spriteHeight{ 150 };
	basic_engine::Rectangle<int32_t> spriteRect{ 0, 0, 64, 64 };

	mSampleSpriteSheet = std::make_unique<SpriteSheet>(cSpriteSheetConfigFile, spriteRect, true);
	if (!mSampleSpriteSheet->Initialize()) {
		spdlog::error("Error in sprite sheet initialization. The config file name is: {}", cSpriteSheetConfigFile);
	}
	mSampleSpriteSheet->Transform().SetPosition(mParameters.Width/2.0F, mParameters.Height / 2.0F);

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlSpriteSheetSample::Update(double tickTimeInMsec) {
	constexpr float speed{ 1.F };
	Vector2f movement{ 0, 0 };

	if (true == mLeftMovementInitiated)	{
		movement.x -= speed;
	}

	if (true == mRightMovementInitiated) {
		movement.x += speed;
	}

	if (true == mTopMovementInitiated) {
		movement.y -= speed;
	}

	if (true == mBottomMovementInitiated) {
		movement.y += speed;
	}

	mSampleSpriteSheet->Transform().Move(movement.x, movement.y);
	mSampleSpriteSheet->Update(tickTimeInMsec);
}

void SdlSpriteSheetSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	// Draw blue lines
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width), static_cast<int32_t>(mParameters.Height) / 2);
	SDL_RenderDrawLine(mRenderer, static_cast<int32_t>(mParameters.Width) / 2, 0, static_cast<int32_t>(mParameters.Width) / 2, static_cast<int32_t>(mParameters.Height));

	mSampleSpriteSheet->Display(mRenderer);
}

void SdlSpriteSheetSample::Finalize() {
}

void SdlSpriteSheetSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	spdlog::info("Current position: <{}, {}>", 
		mSampleSpriteSheet->Transform().Pos().x, mSampleSpriteSheet->Transform().Pos().y);

	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_RIGHT == key) {
			// bu animasyon icin yukari/asagi hareket ve animasyon daha oncelikli
			if (false == mTopMovementInitiated && false == mBottomMovementInitiated) {
				mSampleSpriteSheet->SetAnimation("RightWalking");
			}
			mRightMovementInitiated = true;
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			// bu animasyon icin yukari/asagi hareket ve animasyon daha oncelikli
			if (false == mTopMovementInitiated && false == mBottomMovementInitiated) {
				mSampleSpriteSheet->SetAnimation("LeftWalking");
			}
			mLeftMovementInitiated = true;
		}
		if (KeyboardCodes::KEY_UP == key) {
			mSampleSpriteSheet->SetAnimation("UpWalking");
			mTopMovementInitiated = true;
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			mSampleSpriteSheet->SetAnimation("DownWalking");
			mBottomMovementInitiated = true;
		}
	}

	if (InputActions::ReleaseAction == action) {
		if (KeyboardCodes::KEY_RIGHT == key) {
			mRightMovementInitiated = false;
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			mLeftMovementInitiated = false;
		}
		if (KeyboardCodes::KEY_UP == key) {
			mTopMovementInitiated = false;
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			mBottomMovementInitiated = false;
		}
	}

	// if no key was pressed stop the animation
	if (false == mTopMovementInitiated
		&&
		false == mBottomMovementInitiated
		&&
		false == mLeftMovementInitiated
		&&
		false == mRightMovementInitiated) {
		mSampleSpriteSheet->Stop();
	}
	else {
		mSampleSpriteSheet->Play();
	}
}
