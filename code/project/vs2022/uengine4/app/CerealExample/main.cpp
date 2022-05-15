#include "application_base/window_parameter.h"
#include "application_base/window_parameter_serializer.h"

#include "sprite_sheet/sprite_sheet_parameters.h"
#include "sprite_sheet/sprite_sheet_serializer.h"

#include "utility/json_data_parser.h"

int main() {
	WindowParameter param, param2; 

	JsonDataParser<WindowParameter> wpParser;
	std::cout << "Serialize op result: " << wpParser.Serialize("data.json", param) << "\n";

	auto opResult = wpParser.Deserialize("data.json");
	std::cout << "Deerialize op result: " << opResult.has_value() << "\n";

	basic_engine::SpriteSheetParameters spriteSheetParameters;
	spriteSheetParameters.FrameTime = 200;
	spriteSheetParameters.InitialAnimation = "IdleAnimation";
	spriteSheetParameters.TextureFiles = { { "Main", "SpriteSheet.png" } };

{
		basic_engine::AnimationParameters animation;
		animation.AnimationName = "DownWalking";
		animation.TextureName = "Main";
		animation.AnimationFrames = { {32, 0, 32, 32}, {64, 0, 32, 32}, {32, 0, 32, 32}, {0, 0, 32, 32} };
		spriteSheetParameters.Animations.push_back(animation);
	}

	JsonDataParser<basic_engine::SpriteSheetParameters> SSheetParser;
	std::cout << "Serialize op result: " << SSheetParser.Serialize("SpriteExample.json", spriteSheetParameters) << "\n";

	auto opResult2 = SSheetParser.Deserialize("SpriteExample.json");
	std::cout << "Deerialize op result: " << opResult2.has_value() << "\n";

	/*auto opResult3 = SSheetParser.Deserialize("SpriteExample2.json");
	auto value = opResult3.value();*/

	return 0;
}