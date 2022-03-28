/**
 * @file mouse_event_listener.h
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once
#include <cstdint>

/**
* @enum MouseButtons
* @brief Values that represent mouse buttons
*/
enum class MouseButtons;

/**
* @enum InputActions
* @brief Values that represent �nput actions
*/
enum class InputActions : uint32_t;

/**
* @class MouseEventListener
* @brief A � mouse event listener.
*/
class MouseEventListener {
public:
	/**
	* @brief Mouse button event
	* @param 	button The button.
	* @param 	action The action.
	* @param 	mods   The mods.
	* @param 	x	   The x coordinate.
	* @param 	y	   The y coordinate.
	*/
	virtual void MouseButtonEvent(MouseButtons button, InputActions action, int32_t mods, int32_t x, int32_t y) = 0;
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
