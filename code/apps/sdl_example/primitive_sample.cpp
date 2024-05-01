#include "primitive_sample.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "spdlog/spdlog.h"

PrimitiveSample::PrimitiveSample() {

	mSamples.insert(mSamples.begin(), 
		{ {"Simple Graphic App", mSimpleSample},
		{"Input Sample",  mInputSample},
		{"Texture Sample", mTextureSample},
		{"Gis Asset Sample", mGISAssetSample},
		{"Painter Sample", mPainterSample},
		{"Sprite Sample", mSpriteSample},
		{"Tile Map Sample", mTileMapSample},
		{"Spritesheet Sample", mSpriteSheetSample} });

	mClientGraphicalApplication = std::get<1>(mSamples[7]);

	RegisterEventListener(this);
}

void PrimitiveSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {
	static auto sampleIndex{ 7 };

	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_F12 == key) {
			sampleIndex = (sampleIndex + 1) % mSamples.size();
			spdlog::info("Switching to {}", std::get<0>(mSamples[sampleIndex]));
			UpdateGraphicApplication(std::get<1>(mSamples[sampleIndex]));
		}
		else if (KeyboardCodes::KEY_F11 == key) {
			
			sampleIndex = sampleIndex == 0?(static_cast<int>(mSamples.size())-1):(sampleIndex-1);
			spdlog::info("Switching to {}", std::get<0>(mSamples[sampleIndex]));
			UpdateGraphicApplication(std::get<1>(mSamples[sampleIndex]));
		}
	}
}
