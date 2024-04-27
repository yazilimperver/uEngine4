/**
 * @file primitive_sample.h.
 * @date 10.08.2022
 * @author Yazilimperver
 * @brief  Ornek kabiliyetleri gostermek icin kullailacak olan siniftir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef PRIMITIVESAMPLE_H
#define PRIMITIVESAMPLE_H

#include <vector>

#include "sdl_application/sdl_application.h"

#include "sdl_simple_shape.h"
#include "sdl_input_sample.h"
#include "sdl_sprite_sample.h"
#include "sdl_texture_sample.h"
#include "sdl_sprite_sheet_sample.h"
#include "sdl_tile_map_sample.h"
#include "sdl_painter_sample.h"
#include "sdl_gis_asset_sample.h"

class PrimitiveSample : public SdlApplication, public KeyboardEventListener {
public:
	PrimitiveSample();

private:
	// Ornekler
	std::shared_ptr<SdlPainterSample> mPainterSample{ std::make_shared<SdlPainterSample>() };
	std::shared_ptr<SdlTileMapSample> mTileMapSample{ std::make_shared<SdlTileMapSample>() };
	std::shared_ptr<SdlSpriteSheetSample> mSpriteSheetSample{ std::make_shared<SdlSpriteSheetSample>() };
	std::shared_ptr<SdlSpriteSample> mSpriteSample{ std::make_shared<SdlSpriteSample>() };
	std::shared_ptr<SdlSimpleShape> mSimpleSample{ std::make_shared<SdlSimpleShape>() };
	std::shared_ptr<SdlInputSample> mInputSample{ std::make_shared<SdlInputSample>() };
	std::shared_ptr<SdlTextureSample> mTextureSample{ std::make_shared<SdlTextureSample>() };
	std::shared_ptr<SdlGisAssetSample> mGISAssetSample{ std::make_shared<SdlGisAssetSample>() };

	std::vector< std::pair<std::string, std::shared_ptr<ClientGraphicApplication>> > mSamples;

	// Inherited via KeyboardEventListener
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif // !PRIMITIVESAMPLE_H

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

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
