/**
 * @file sdl_simple_shape.h.
 * @date 28.03.2022
 * @author Yazilimperver
 * @brief https://lazyfoo.net/tutorials/SDL/08_geometry_rendering/index.php sayfasindan Geometry Rendering ornegi
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLSIMPLESHAPE_H
#define SDLSIMPLESHAPE_H


#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"

struct SDL_Renderer;

class SdlSimpleShape : public ClientGraphicApplication {
public:
	// Inherited via ClientGraphicApplication
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;
};
#endif // !SDLSIMPLESHAPE_H