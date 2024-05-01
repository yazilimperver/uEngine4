/**
 * @file falling_letters_app.h.
 * @date 8.11.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef FALLING_LETTERS_APP_H
#define FALLING_LETTERS_APP_H

#include "application_base/keyboard_event_listener.h"

#include "sdl_application/sdl_application.h"

#include "falling_letters_graphics_app.h"

/**
 * @class FallingLettersApp
 * @brief Düþen harfler için kullanacaðýmýz uygulama sýnýfý
 */
class FallingLettersApp 
	: public SdlApplication, // (1)
	  public KeyboardEventListener  { // (2)
public:
	FallingLettersApp();

	//! @brief Klavye girdileri için kullanacaðýmýz fonksiyon (3)
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
private:
	/** @brief Grafik uygulamamýz. Asýl iþlevler bu sýnýf içerisinde tanýmlanýyor olacak (4) */
	std::shared_ptr<FallingLettersGraphicApp> mApp{ std::make_shared<FallingLettersGraphicApp>() };
};

#endif // !FALLING_LETTERS_APP_H

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
