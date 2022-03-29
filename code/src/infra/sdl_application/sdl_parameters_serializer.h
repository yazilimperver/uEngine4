#ifndef SDLPARAMETERSSERIALIZER_H
#define SDLPARAMETERSSERIALIZER_H
/**
 * @file sdl_parameters_serializer.h.
 * @date 29.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#include "sdl_parameters.h"

#include <cereal/archives/json.hpp>

template<class Archive>
void serialize(Archive& archive, SdlParameters& m) {
	archive(cereal::make_nvp("Samples", m.Samples),
		cereal::make_nvp("DepthSize", m.DepthSize),
		cereal::make_nvp("MajorVersion", m.MajorVersion),
		cereal::make_nvp("MinorVersion", m.MinorVersion),
		cereal::make_nvp("IsResizable", m.IsResizable),
		cereal::make_nvp("IsDisplayEventLogs", m.IsDisplayEventLogs));
}

#endif // !SDLPARAMETERSSERIALIZER_H