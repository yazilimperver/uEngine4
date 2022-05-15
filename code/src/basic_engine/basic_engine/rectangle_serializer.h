#ifndef RECTANGLESERIALIZER_H_
#define RECTANGLESERIALIZER_H_

#include <cereal/archives/json.hpp>
#include "rectangle.h"

namespace basic_engine {
	template<class Archive, typename T>
	void serialize(Archive& archive, basic_engine::Rectangle<T>& m) {
		archive(cereal::make_nvp("Left", m.Left),
			cereal::make_nvp("Top", m.Top),
			cereal::make_nvp("Width", m.Width),
			cereal::make_nvp("Height", m.Height));
	}
}

#endif // !RECTANGLESERIALIZER_H_

