#include "sdl_gis_asset_sample.h"

#include "SDL.h"

#include "gis_asset/gis_map_asset.h"
#include "sdl_application/sdl_application.h"
#include "gis_asset/gis_map_loader.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "basic_engine/game.h"

#include "spdlog/spdlog.h"

using namespace basic_engine;
using namespace gis_asset;

constexpr Point2d screenCenter{ 320, 240 };

void SdlGisAssetSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	mPainter.AssignRenderer(mRenderer);

	auto mapLoader = std::make_unique<GisMapLoader>();
	mapLoader->AssignRenderer(mRenderer);

	mGisAsset = std::move(mapLoader->Load("ExampleRaster.png", "raster_tile"));

	mMapCenter = screenCenter;

	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
}

void SdlGisAssetSample::Update(double tickTimeInMsec) {
}

void SdlGisAssetSample::Display(double tickTimeInMsec) {


	// Ekrani sil
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	// Mavi cizgileri cizelim
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width), static_cast<int32_t>(mParameters.Height) / 2);
	SDL_RenderDrawLine(mRenderer, static_cast<int32_t>(mParameters.Width) / 2, 0, static_cast<int32_t>(mParameters.Width) / 2, static_cast<int32_t>(mParameters.Height));

	auto gisAsset = dynamic_cast<GisMapAsset*>(mGisAsset.get());
	mPainter.DrawTexture(gisAsset->Texture(), mMapCenter, gisAsset->Width(), gisAsset->Height());
}

void SdlGisAssetSample::Finalize() {
}

void SdlGisAssetSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	spdlog::info("Current position: <{}, {}>", mMapCenter.x, mMapCenter.y);
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			mMapCenter.y += 5.0;
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mMapCenter.y -= 5.0;
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mMapCenter.x -= 5.0;
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mMapCenter.x += 5.0;
		}
	}
}
