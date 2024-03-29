/**
 * @file sdl_parameters_serializer.h.
 * @date 29.03.2022
 * @author Yazilimperver
 * @brief
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef SDLPARAMETERSSERIALIZER_H
#define SDLPARAMETERSSERIALIZER_H

#include "sdl_parameters.h"

#include <cereal/archives/json.hpp>

template<class Archive>
void serialize(Archive& archive, SdlParameters& m) {
	archive(cereal::make_nvp("DepthSize", m.DepthSize),
		cereal::make_nvp("MajorVersion", m.MajorVersion),
		cereal::make_nvp("MinorVersion", m.MinorVersion),
		cereal::make_nvp("IsResizable", m.IsResizable),
		cereal::make_nvp("IsDisplayEventLogs", m.IsDisplayEventLogs),
		cereal::make_nvp("IsGLEnabled", m.IsGLEnabled));
}

#endif // !SDLPARAMETERSSERIALIZER_H

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
