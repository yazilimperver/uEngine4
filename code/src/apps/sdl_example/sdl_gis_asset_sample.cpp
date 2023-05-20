#include "sdl_gis_asset_sample.h"

#include "SDL.h"

#include "spdlog/spdlog.h"

#include "sdl_application/sdl_application.h"

#include "gis_asset/gis_map_asset.h"
#include "gis_asset/gis_map_loader.h"

#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"

#include "basic_engine/game.h"

#include "painter/gfx_primitives.h"

#include "core_gis/slippy_map_util.h"
#include "pager/tile_id.h"

using namespace basic_engine;
using namespace gis_asset;

void SdlGisAssetSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();
	mMapView = std::make_unique<gis::MapView>(mParameters.Width, mParameters.Height, cScreenGeoCenter, cZoomLevel);
	mPainter.AssignRenderer(mRenderer);

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));
	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
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

void SdlGisAssetSample::Update(double tickTimeInMsec) {
}

void SdlGisAssetSample::Display(double tickTimeInMsec) {
	// Ekrani sil
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	gfxPrimitivesSetFont(nullptr, 8 * 4, 8 * 4);

	PointInPixels viewCenter = mMapView->CenterInPixels();
	auto centerGoogleTileInfo = gis::TileTms::PixelToTile(viewCenter, cZoomLevel).ObtainGoogleTileInfo();
	
	int32_t googleTileX = centerGoogleTileInfo.x;
	int32_t googleTileY = centerGoogleTileInfo.y - cRadius;

	for (int32_t i = 0; i < cTilePerAxis; i++) {
		googleTileX = centerGoogleTileInfo.x - cRadius;

		for (int32_t j = 0; j < cTilePerAxis; j++) {
			auto tileToUse = gis::TileTms::FromGoogleTile({ googleTileX, googleTileY }, cZoomLevel);
			auto tileBound = tileToUse.PixelBoundsTopLeftBottomRigth();
			auto geogBounds = tileToUse.GeographicBounds();
			auto westSouth = std::get<0>(geogBounds);
			auto eastNorth = std::get<1>(geogBounds);

			double centerLong = (eastNorth.Longitude() + westSouth.Longitude()) / 2.0;
			double centerLat = (eastNorth.Latitude() + westSouth.Latitude()) / 2.0;

			SDL_Rect tileRect{ std::get<0>(tileBound).x - viewCenter.x + 320, std::get<0>(tileBound).y - viewCenter.y + 240, cTileSize, cTileSize };
			mPainter.AssignPen(Pen{ Color::Blue, 3 });
			mPainter.AssignBrush(Brush{ Color::Black });
			mPainter.DrawRectangle(tileRect);

			gis::TileId tileToDisplay{ googleTileX, googleTileY, cZoomLevel };

			char tileStr[128];

			sprintf(tileStr, "Pos:<%05.3f, %05.3f>", centerLat, centerLong);
			stringRGBA(mRenderer, static_cast<Sint16>(tileRect.x + cTileSize * 0.15), static_cast<Sint16>(tileRect.y + cTileSize * 0.5), tileStr, 255, 0, 0, 255);

			sprintf(tileStr, "Pix:<%d, %d>", tileRect.x + static_cast<int>(tileRect.w/2), static_cast<int>(tileRect.y + tileRect.h / 2));
			stringRGBA(mRenderer, static_cast<Sint16>(tileRect.x + cTileSize * 0.15), static_cast<Sint16>(tileRect.y + cTileSize * 0.55), tileStr, 0, 255, 255, 255);
			
			sprintf(tileStr, "TMS:<%d, %d>", tileToUse.TmsX(), tileToUse.TmsY());
			stringRGBA(mRenderer, static_cast<Sint16>(tileRect.x + cTileSize * 0.15), static_cast<Sint16>(tileRect.y + cTileSize * 0.6), tileStr, 0, 255, 0, 255);

			sprintf(tileStr, "GGL:<%d, %d>", googleTileX, googleTileY);
			stringRGBA(mRenderer, static_cast<Sint16>(tileRect.x + cTileSize * 0.15), static_cast<Sint16>(tileRect.y + cTileSize * 0.65), tileStr, 255, 255, 0, 255);
			
			googleTileX++;
		}

		googleTileY++;
	}

	mPainter.AssignPen(Pen{ Color::Magenta, 3 });
	mPainter.AssignBrush(Brush{ Color::Magenta});
	mPainter.DrawEllipse(Point2d{ 320, 240 }, 5, 5);
	stringRGBA(mRenderer, 300, 245, "Center", Color::Magenta.R, Color::Magenta.G, Color::Magenta.B, 255);

	// Ekranin piksel karsiliklari
	stringRGBA(mRenderer, 0, 0, "<0, 0>", Color::Yellow.R, Color::Yellow.G, Color::Yellow.B, 255);
	stringRGBA(mRenderer, mParameters.Width - 80, 0, "<640, 0>", Color::Yellow.R, Color::Yellow.G, Color::Yellow.B, 255);
	stringRGBA(mRenderer, mParameters.Width - 80, mParameters.Height - 10, "<640, 480>", Color::Yellow.R, Color::Yellow.G, Color::Yellow.B, 255);
	stringRGBA(mRenderer, 0, mParameters.Height - 10, "<0, 480>", Color::Yellow.R, Color::Yellow.G, Color::Yellow.B, 255);
	
	auto linesToDisplay = SplitString(mMapView->InfoText());
	for (size_t i = 0; i < linesToDisplay.size(); ++i) {
		stringRGBA(mRenderer, 10, static_cast<int16_t>(10 + 10 * i), linesToDisplay[i].c_str(), Color::Green.R, Color::Green.G, Color::Green.B, 255);
	}
}

void SdlGisAssetSample::Finalize() {
}

void SdlGisAssetSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			mMapView->MoveInPixel(0, -10);
		}
		if (KeyboardCodes::KEY_DOWN == key) {
			mMapView->MoveInPixel(0, 10);
		}
		if (KeyboardCodes::KEY_RIGHT == key) {
			mMapView->MoveInPixel(10, 0);
		}
		if (KeyboardCodes::KEY_LEFT == key) {
			mMapView->MoveInPixel(-10, 0);
		}
	}
}
