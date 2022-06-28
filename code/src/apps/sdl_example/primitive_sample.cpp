#include "primitive_sample.h"

#include "sdl_simple_shape.h"
#include "sdl_input_sample.h"
#include "sdl_sprite_sample.h"
#include "sdl_texture_sample.h"
#include "sdl_sprite_sheet_sample.h"
#include "sdl_tile_map_sample.h"

PrimitiveSample::PrimitiveSample() {
	//mClientGraphicalApplication = std::make_shared<SdlTileMapSample>();
	//mClientGraphicalApplication = std::make_shared<SdlSpriteSheetSample>();
	//mClientGraphicalApplication = std::make_shared<SdlSpriteSample>();
	mClientGraphicalApplication = std::make_shared<SdlSimpleShape>();
	//mClientGraphicalApplication = std::make_shared<SdlInputSample>();
	//mClientGraphicalApplication = std::make_shared<SdlTextureSample>();
}
