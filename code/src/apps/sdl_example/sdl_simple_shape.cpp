#include "sdl_simple_shape.h"

#include "SDL.h"

#include "sdl_application/sdl_application.h"

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
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0x00, 0x00, 0xFF);
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
}

void SdlSimpleShape::Finalize()
{
}
