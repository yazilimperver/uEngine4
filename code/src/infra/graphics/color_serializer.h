/**
 * @file window_parameter_serializer.h.
 * @date 20.03.2022
 * @author Yazilimperver
 * @brief  Renk veri yapisinin `serialization/deserialization` adaptoru
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef COLOR_SERIALIZER
#define COLOR_SERIALIZER

#include "color.h"
#include <cereal/archives/json.hpp>

template<class Archive>
void serialize(Archive& archive, Color& m) {
	archive(cereal::make_nvp("Red", m.R),
		cereal::make_nvp("Green", m.G),
		cereal::make_nvp("Blue", m.B),
		cereal::make_nvp("Alpha", m.A));
}

#endif /* COLOR_SERIALIZER */

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
