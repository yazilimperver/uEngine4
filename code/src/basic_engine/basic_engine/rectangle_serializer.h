#ifndef RECTANGLESERIALIZER_H_
#define RECTANGLESERIALIZER_H_

#include <cereal/archives/json.hpp>
#include "rectangle.h"

namespace basic_engine {
	template<class Archive, typename T>
	void serialize(Archive& archive, basic_engine::Rectangle<T>& m) {
		archive(cereal::make_nvp("Left", m.mLeft),
			cereal::make_nvp("Top", m.mTop),
			cereal::make_nvp("Width", m.mWidth),
			cereal::make_nvp("Height", m.mHeight));
	}
}

#endif // !RECTANGLESERIALIZER_H_

