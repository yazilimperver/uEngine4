/**
 * @file   sdl_gis_asset_sample.h
 * @date   4/11/2023
 * @author Yazilimperver
 * @brief  SDL Paınter sınıfı ve CBS kabiliyetleri kullanılarak TMS ve Google Pafta bilgilerinin gösterilmesine yönelik örnek uygulamadır.
 * @remark
 */

#ifndef INC_SDL_GIS_ASSET_SAMPLE_H
#define INC_SDL_GIS_ASSET_SAMPLE_H

#include <memory>

#include "painter/painter.h"

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "gis_asset/gis_map_asset.h"

#include "core_gis/map_view.h"

struct SDL_Renderer;

class SdlGisAssetSample
	: public ClientGraphicApplication, public KeyboardEventListener {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	
	/** @brief Ornek icin kullanilacak olan bir takim sabitler */
	const int32_t cTilePerAxis{ 5 };
	const int32_t cRadius = cTilePerAxis / 2;
	const int32_t cTileSize{ 256 };
	const Point2d cScreenCenter{ 320, 240 };
	const gis::GeoPoint cScreenGeoCenter{ 39.9, 32.5 };
	const uint32_t cZoomLevel = 10;

	/** @brief Uygulama penceresine yönelik konfigürasyon parametreleri */
	WindowParameter mParameters;

	/** @brief SDL Renderer nesnesi */
	SDL_Renderer* mRenderer{ nullptr };

	/** @brief SDL Painter nesnesi */
	basic_engine::Painter mPainter;
	
	/** @brief Pencerenin coğrafik ifadesi için kullanilacak olan nesnedir */
	std::unique_ptr<gis::MapView> mMapView;

	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};


#endif	// INC_SDL_GIS_ASSET_SAMPLE_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


