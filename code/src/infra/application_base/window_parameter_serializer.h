/**
 * @file window_parameter_serializer.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief WindowParameter veri yapisinin `serialization/deserialization` adaptoru
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef WINDOW_PARAMETER_SERIALIZER
#define WINDOW_PARAMETER_SERIALIZER

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

#endif /* WINDOW_PARAMETER_SERIALIZER */

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
