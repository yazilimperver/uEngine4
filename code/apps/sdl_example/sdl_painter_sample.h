/**
 * @file sdl_painter_sample.h.
 * @date 29.07.2022
 * @author Yazilimperver
 * @brief  SDL tabanl� temel "painter" s�n�f�m�z�n kullan�m�n� g�steren ornektir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLPAINTERSAMPLE_H
#define SDLPAINTERSAMPLE_H

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"

#include "painter/painter.h"

#include "basic_engine/sprite.h"

struct SDL_Renderer;

class SdlPainterSample : public ClientGraphicApplication {
public:
	// Inherited via ClientGraphicApplication
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;

	std::unique_ptr<basic_engine::Sprite> mSampleSprite;

	basic_engine::Painter mPainter;
};
#endif // !SDLPAINTERSAMPLE_H

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
