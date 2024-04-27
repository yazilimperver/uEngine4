#include "sdl_tile_map_sample.h"
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
// 
using namespace basic_engine;


void SdlTileMapSample::Initialize(SdlApplication& sdlApplication){
	mSdlApplication = &sdlApplication;
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	Game::AssignWindowParameters(mParameters);
	Game::GameCamera().Initialize(mParameters);

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	dynamic_cast<infra::AssetRepository&>(Game::GetAssetService()).AssignRenderer(mRenderer);

	Game::GetAssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	mSampleTileMap = std::make_unique<basic_engine::TileMap>(ASSET_ROOT_PATH + "tilemap/example/" + "example.tmj");
	mSampleTileMap->Initialize(ASSET_ROOT_PATH + "tilemap/example/");

	targetPos = { static_cast<int32_t>(mParameters.Width) * 0.5F, static_cast<int32_t>(mParameters.Height) * 0.5F };

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlTileMapSample::Update(double tickTimeInMsec) {
	mSampleTileMap->Update(tickTimeInMsec);
	Game::GameCamera().Update(tickTimeInMsec);
	Game::GameCamera().DisplayInfo();
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

	constexpr int32_t cIncrementAmount{ 5 };
	bool updateTarget{ false };
	
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			targetPos.y -= cIncrementAmount;
			updateTarget = true;
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			targetPos.y += cIncrementAmount;
			updateTarget = true;
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			targetPos.x += cIncrementAmount;
			updateTarget = true;
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			targetPos.x -= cIncrementAmount;
			updateTarget = true;
		}

		if (true == updateTarget) {
			targetPos.x = glm::clamp(targetPos.x, 0, (4 * static_cast<int32_t>(mParameters.Width)));
			targetPos.y = glm::clamp(targetPos.y, 0, (4 * static_cast<int32_t>(mParameters.Height)));

			Game::GameCamera().SetTarget(targetPos);
		}
	}
}
