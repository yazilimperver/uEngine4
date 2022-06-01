#include "sdl_tile_map_sample.h"
#include "SDL.h"

#include "sdl_application/sdl_application.h"
#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

using namespace basic_engine;

void SdlTileMapSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	dynamic_cast<AssetRepository&>(Game::AssetService()).AssignRenderer(mRenderer);

	Game::AssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	mSampleTileMap = std::make_unique<basic_engine::TileMap>("./tilemap/example/example.tmj");
	mSampleTileMap->Initialize();

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlTileMapSample::Update(double tickTimeInMsec) {
	mSampleTileMap->Update(tickTimeInMsec);
}

void SdlTileMapSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	// Draw blue lines
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width), static_cast<int32_t>(mParameters.Height) / 2);
	SDL_RenderDrawLine(mRenderer, static_cast<int32_t>(mParameters.Width) / 2, 0, static_cast<int32_t>(mParameters.Width) / 2, static_cast<int32_t>(mParameters.Height));

	mSampleTileMap->Display(mRenderer);
}

void SdlTileMapSample::Finalize() {
}

void SdlTileMapSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {

	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
		}
	}
}
