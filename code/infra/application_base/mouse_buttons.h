/**
 * @file mouse_buttons.h
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief Fare tuslarini temsil eden enumeratordur
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef MOUSE_BUTTONS
#define MOUSE_BUTTONS

#include <cstdint>

enum class MouseButtons : int32_t {
	MouseButton1 = 0,
	MouseButton2 = 1,
	MouseButton3 = 2,
	MouseButton4 = 3,
	MouseButton5 = 4,
	MouseButton6 = 5,
	MouseButton7 = 6,
	MouseButton8 = 7,
	MouseButtonLast   = MouseButton8,
	MouseButtonLeft   = MouseButton1,
	MouseButtonRight  = MouseButton2,
	MouseButtonMiddle = MouseButton3,
	MouseButtonNone
};

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


#endif /* MOUSE_BUTTONS */
