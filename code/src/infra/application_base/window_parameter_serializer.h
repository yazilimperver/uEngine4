/**
 * @file window_parameter_serializer.h.
 * @date 20.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include "window_parameter.h"
#include "graphics/color_serializer.h"

#include <cereal/archives/json.hpp>

template<class Archive>
void serialize(Archive& archive, WindowParameter& m) {
	archive(cereal::make_nvp("Title", m.Title),
		cereal::make_nvp("Width", m.Width),
		cereal::make_nvp("Height", m.Height),
		cereal::make_nvp("Top", m.Top),
		cereal::make_nvp("Left", m.Left),
		cereal::make_nvp("ClearColor", m.ClearColor),
		cereal::make_nvp("IsFullScreen", m.IsFullScreen),
		cereal::make_nvp("IsVsyncEnabled", m.IsVSYNCEnabled));
}
