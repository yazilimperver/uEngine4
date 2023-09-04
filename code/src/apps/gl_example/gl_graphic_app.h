/**
 * @file   gmap_graphic_app.h
 * @date   4/11/2023
 * @author Yazilimperver
 * @brief  GMap icin kullanacagimiz grafik uygulamamiz
 * @remark
 */

#ifndef INC_SDL_GIS_ASSET_SAMPLE_H
#define INC_SDL_GIS_ASSET_SAMPLE_H

#include <memory>
#include <unordered_map>

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "gl_painter/gl_basic_painter.h"

struct SDL_Renderer;

class GLGraphicApp
	: public ClientGraphicApplication
	, public KeyboardEventListener{
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
    bool mEnableRotatingCubeExample{false};
	SDL_Renderer* mRenderer{ nullptr };
    SdlApplication* mSDLApplication{ nullptr };
    std::optional<AssetHandle> mTextureAssetHandle;
	WindowParameter mParameters;
	gl::GLBasicPainter mPainter;
	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};


#endif	// INC_SDL_GIS_ASSET_SAMPLE_H

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


