#include "application_base/window_parameter.h"
#include "application_base/window_parameter_serializer.h"

#include "utility/json_data_parser.h"


int main() {
	WindowParameter param, param2; 

	JsonDataParser<WindowParameter> wpParser;
	std::cout << "Serialize op result: " << wpParser.Serialize("data.json", param) << "\n";

	auto opResult = wpParser.Deserialize("data.json");
	std::cout << "Deerialize op result: " << opResult.has_value() << "\n";

	return 0;
}