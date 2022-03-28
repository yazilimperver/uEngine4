/**
 * @file touch_event_handler.h
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once
#include <cstdint>

/**
* @enum TouchAction
* @brief Values that represent touch actions
*/
enum class TouchAction;

/**
* @struct TouchData
* @brief A touch data.
*/
struct TouchData;

/**
* @class TouchService
* @brief A service for accessing � touches information.
*/
class TouchService;

/**
* @class TouchEventHandler
* @brief A touch event handler.
*/
class TouchEventHandler {
public:
	/**
	* @brief Initializes the given touch adapter
	* @param [in,out]	touchAdapter If non-null, the touch adapter.
	*/
	virtual void Initialize(TouchService* touchAdapter) = 0;

	/**
	* @brief Touch event
	* @param action    The action.
	* @param touchData Information describing the touch.
	*/
	virtual void TouchEvent(TouchAction action, const TouchData& touchData) = 0;
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
