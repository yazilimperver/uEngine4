/**
 * @file sdl_painter_sample.h.
 * @date 29.07.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLPAINTERSAMPLE_H
#define SDLPAINTERSAMPLE_H

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"

#include "painter/painter.h"

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

	basic_engine::Painter mPainter;
};
#endif // !SDLPAINTERSAMPLE_H
