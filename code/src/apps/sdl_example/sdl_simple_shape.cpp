#include "sdl_simple_shape.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"

#include "basic_engine/gfx_primitives.h"

void SdlSimpleShape::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();
}

void SdlSimpleShape::Update(double tickTimeInMsec) {
}

void SdlSimpleShape::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);
	
	//Render red filled quad
	SDL_Rect fillRect = { static_cast<int32_t>(mParameters.Width) / 4, static_cast<int32_t>(mParameters.Height) / 4, static_cast<int32_t>(mParameters.Width)  / 2, static_cast<int32_t>(mParameters.Height) / 2 };
	/*SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(mRenderer, &fillRect);

	//Render green outlined quad
	SDL_Rect outlineRect = { static_cast<int32_t>(mParameters.Width)  / 6, static_cast<int32_t>(mParameters.Height) / 6, static_cast<int32_t>(mParameters.Width)  * 2 / 3, static_cast<int32_t>(mParameters.Height) * 2 / 3 };
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(mRenderer, &outlineRect);

	//Draw blue horizontal line
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(mRenderer, 0, static_cast<int32_t>(mParameters.Height) / 2, static_cast<int32_t>(mParameters.Width) , static_cast<int32_t>(mParameters.Height) / 2);

	//Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0x00, 0xFF);
	for (int i = 0; i < static_cast<int32_t>(mParameters.Height); i += 4)	{
		SDL_RenderDrawPoint(mRenderer, static_cast<int32_t>(mParameters.Width)  / 2, i);
	}
	*/
	
	boxRGBA(mRenderer, mParameters.Width, 0, 0, mParameters.Height, 0, 255, 0, 255);
	roundedBoxRGBA(mRenderer, fillRect.x + fillRect.w, fillRect.y, fillRect.x, fillRect.y + fillRect.h, 25, 255, 0, 0, 255);
	filledCircleRGBA(mRenderer, fillRect.x + fillRect.w * 0.5, fillRect.y + fillRect.h * 0.5, 100, 0, 0, 255, 255);

	gfxPrimitivesSetFont(nullptr, 8 * 4, 8 * 4);

	stringRGBA(mRenderer, fillRect.x + fillRect.w * 0.5, fillRect.y + fillRect.h * 0.5, "Merhaba dunya", 255, 255, 255, 255);
}

void SdlSimpleShape::Finalize()
{
}
