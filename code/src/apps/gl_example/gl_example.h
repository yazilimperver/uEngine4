/**
 * @file   gmap.h
 * @date   4/20/2023
 * @author Yazilimperver
 * @brief  Jenerik harita uygulamasi
 * @remark
 */

#ifndef INC_GMAP_H
#define INC_GMAP_H

#include <vector>

#include "sdl_application/sdl_application.h"
#include "gl_graphic_app.h"

class GLExample
	: public SdlApplication, public KeyboardEventListener {
public:
	GLExample();

private:
	// Gorsel isleri yurutecek olan sinifimiz
	std::shared_ptr<GLGraphicApp> mGLGraphicApp{ std::make_shared<GLGraphicApp>() };

	// Inherited via KeyboardEventListener
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif	// INC_GMAP_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

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


