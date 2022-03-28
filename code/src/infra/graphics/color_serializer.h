/**
 * @file window_parameter_serializer.h.
 * @date 20.03.2022
 * @author Yazilimperver
 * @brief
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include "color.h"
#include <cereal/archives/json.hpp>

template<class Archive>
void serialize(Archive& archive, Color& m) {
	archive(cereal::make_nvp("Red", m.R),
		cereal::make_nvp("Green", m.G),
		cereal::make_nvp("Blue", m.B),
		cereal::make_nvp("Alpha", m.A));
}

