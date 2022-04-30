/**
 * @file keyboard_event_listener.h
 * @date 15.03.2022
 * @author Yazilimperver
 * @brief  Klavye girdilerini dinlemek icin kullanilacak olan arayuzdur
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef KEYBOARD_EVENT_LISTENER
#define KEYBOARD_EVENT_LISTENER
#include <cstdint>

enum class InputActions : uint32_t;
enum class KeyboardCodes;
enum class KeyboardModifier;

class KeyboardEventListener {
public:
	/**
		* @brief ! Keyboard event handler class ! For mods include uKeyboardModifiers
		* @param 	key		 The key.
		* @param 	scancode The scancode.
		* @param 	action   The action.
		* @param 	mods	 The mods.
		*/
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) = 0;
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

#endif /* KEYBOARD_EVENT_LISTENER */