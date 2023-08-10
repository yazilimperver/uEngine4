#include "map_viewer_client_app.h"

#include <regex>

#include "SDL.h"

#include "sdl_application/sdl_application.h"
#include "asset/asset_repository.h"
#include "sdl_asset/sdl_texture_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

#include "painter/gfx_primitives.h"

using namespace basic_engine;

void MapViewerClientApp::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	mMapView = std::make_unique<gis::MapView>(mParameters.Width, mParameters.Height, gis::GeoPoint{ 38, 31 }, 6);

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	dynamic_cast<infra::AssetRepository&>(Game::GetAssetService()).AssignRenderer(mRenderer);

	Game::GetAssetService().RegisterLoader(std::move(std::make_unique<SdlTextureLoader>()));

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void MapViewerClientApp::Update(double tickTimeInMsec) {
}

std::vector<std::string> SplitString(const std::string& str)
{
	std::vector<std::string> tokens;

	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, '\n')) {
		tokens.push_back(token);
	}

	return tokens;
}

void MapViewerClientApp::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	//Render red filled quad
	SDL_Rect fillRect = { static_cast<int32_t>(mParameters.Width) / 4, static_cast<int32_t>(mParameters.Height) / 4, static_cast<int32_t>(mParameters.Width) / 2, static_cast<int32_t>(mParameters.Height) / 2 };
	
	boxRGBA(mRenderer, mParameters.Width, 0, 0, mParameters.Height, 0, 255, 0, 255);
	roundedBoxRGBA(mRenderer, fillRect.x + fillRect.w, fillRect.y, fillRect.x, fillRect.y + fillRect.h, 25, 255, 0, 0, 255);
	filledCircleRGBA(mRenderer, static_cast<int16_t>(fillRect.x + fillRect.w * 0.5), static_cast<int16_t>(fillRect.y + fillRect.h * 0.5), 100, 0, 0, 255, 255);

	gfxPrimitivesSetFont(nullptr, 8 * 4, 8 * 4);

	auto linesToDisplay = SplitString(mMapView->InfoText());
	for (size_t i = 0; i < linesToDisplay.size(); ++i) {
		stringRGBA(mRenderer, 10, static_cast<int16_t>(10 + 10 * i), linesToDisplay[i].c_str(), 0, 0, 0, 255);
	}
}

void MapViewerClientApp::Finalize() {
}

void MapViewerClientApp::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			mMapView->MoveInPixel(0, -10);
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mMapView->MoveInPixel(0, 10);
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mMapView->MoveInPixel(10, 0);
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mMapView->MoveInPixel(-10, 0);
		}
		if (KeyboardCodes::KEY_PAGE_UP == key) {
			spdlog::info("Rotate right pressed");
		}
		if (KeyboardCodes::KEY_PAGE_DOWN == key) {
			spdlog::info("Rotate right pressed");
		}
		if (KeyboardCodes::KEY_KP_ADD == key) {
			spdlog::info("Scale up pressed");
		}
		if (KeyboardCodes::KEY_KP_SUBTRACT == key) {
			spdlog::info("Scale down pressed");
		}
	}
}
