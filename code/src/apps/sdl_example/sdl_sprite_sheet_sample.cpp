#include "sdl_sprite_sheet_sample.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"
#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

#include "configuration.h"

// Asset dizini CMake uzerinden veriliyor (ASSET_ROOT_PATH) olacak. Ornekler de bunu kullaniyor olacak

using namespace basic_engine;

static const std::string cSpriteSheetConfigFile = "warrior_idle_ssheet.json";

void SdlSpriteSheetSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));
	dynamic_cast<AssetRepository&>(Game::GetAssetService()).AssignRenderer(mRenderer);
	Game::GetAssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	infra::Rectangle<int32_t> spriteRect{ 0, 0, 128, 128};

	mSampleSpriteSheet = std::make_unique<SpriteSheet>(ASSET_ROOT_PATH, cSpriteSheetConfigFile, spriteRect, false);
	if (!mSampleSpriteSheet->Initialize()) {
		spdlog::error("Error in sprite sheet initialization. The config file name is: {}", cSpriteSheetConfigFile);
	}
	mSampleSpriteSheet->SetPosition(static_cast<int>(mParameters.Width/2.0F), static_cast<int>(mParameters.Height / 2.0F));
}

void SdlSpriteSheetSample::Update(double tickTimeInMsec) {
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
	
	auto spriteTransform = mSampleSpriteSheet->Transform();
	auto spriteTransformPos = spriteTransform.Pos();

	spdlog::info("Current position: <{}, {}>", 
		spriteTransformPos.x, spriteTransformPos.y);
	
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mSampleSpriteSheet->SetAnimation("Walk");
			mSampleSpriteSheet->SetPosition(spriteTransformPos.x + 5, spriteTransformPos.y);

			if (mSampleSpriteSheet->IsHorizontalFlipped()) {
				mSampleSpriteSheet->DisableFlip();
			}

			mRightMovementInitiated = true;
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mSampleSpriteSheet->SetAnimation("Walk");
			if (false == mSampleSpriteSheet->IsHorizontalFlipped()) {
				mSampleSpriteSheet->EnableHorizontalFlipped();
			}

			mSampleSpriteSheet->SetPosition(spriteTransformPos.x - 5, spriteTransformPos.y);

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
		mSampleSpriteSheet->SetAnimation("Idle");
	}
}
