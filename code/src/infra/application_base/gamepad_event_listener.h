/**
 * @file gamepad_event_listener.h.
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief  Gamepad olaylarini dinlemek icin kullanilacak olan servis arayuzudur
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef GAMEPAD_EVENT_LISTENER
#define GAMEPAD_EVENT_LISTENER

#include <cstdint>
#include <string_view>
#include "input_actions.h"

struct GamepadButtonData;
struct GamepadAxisData;
class GamepadEventListener {
public:
	/**
		* @brief  Gamepad events that will be provided to listener in case of event happening
		* @param 	controllerIndex The controller �ndex.
		* @param 	inputAction	    The input action.
		* @param 	buttonData	    Information describing the button.
		*/
	virtual void GamepadEvent(int32_t controllerIndex, InputActions inputAction, const GamepadButtonData& buttonData) = 0;

	/**
		* @brief Gamepad event
		* @param 	controllerIndex The controller �ndex.
		* @param 	axisData	    Information describing the axis.
		*/
	virtual void GamepadEvent(int32_t controllerIndex, const GamepadAxisData& axisData) = 0;

	/**
		* @brief Gamepad controller added
		* @param 	nameOfController Name of the controller.
		* @param 	gamepadID		 The gamepad ID.
		*/
	virtual void GamepadControllerAdded(std::string_view nameOfController, int32_t gamepadID) = 0;

	/**
		* @brief Gamepad controller removed
		* @param 	nameOfController Name of the controller.
		* @param 	gamepadID		 The gamepad ID.
		*/
	virtual void GamepadControllerRemoved(std::string_view nameOfController, int32_t gamepadID) = 0;
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


#endif /* GAMEPAD_EVENT_LISTENER */
