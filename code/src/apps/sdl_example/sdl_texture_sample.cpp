#include "sdl_texture_sample.h"

#include "SDL_image.h"

#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"

#include "spdlog/spdlog.h"

#include "configuration.h"

// Asset dizini CMake uzerinden veriliyor (ASSET_ROOT_PATH) olacak. Ornekler de bunu kullaniyor olacak

SDL_Texture* SdlTextureSample::LoadTexture(std::string path) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (newTexture == NULL)		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void SdlTextureSample::Initialize(SdlApplication& sdlApplication) {
	mRenderer = sdlApplication.GetSdlRenderer();
	mParameters = sdlApplication.GetWindowParametrs();

	sdlApplication.RegisterEventListener(static_cast<KeyboardEventListener*>(this));

	//Initialize renderer color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))	{
		spdlog::error("SDL_image could not initialize! SDL_image Error: {}", IMG_GetError());
	}

	//Load PNG texture
	mTexture = LoadTexture(ASSET_ROOT_PATH + "texture.png");
	if (mTexture == NULL)	{
		spdlog::error("Failed to load texture image!");
	}
}

void SdlTextureSample::Update(double tickTimeInMsec) {
}

void SdlTextureSample::Display(double tickTimeInMsec) {
	//Clear screen
	SDL_RenderClear(mRenderer);

	//Render texture to screen
	SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);

	//Update screen
	SDL_RenderPresent(mRenderer);
}

void SdlTextureSample::Finalize() {
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	IMG_Quit();
}

void SdlTextureSample::KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) {

	if (InputActions::PressAction == action) {
		if (KeyboardCodes::KEY_UP == key) {
			spdlog::info("Up key pressed");
			mCenter.y -= 1;
		}
		else if (KeyboardCodes::KEY_DOWN == key) {
			spdlog::info("Down key pressed");
			mCenter.y += 1;
		}
		else if (KeyboardCodes::KEY_RIGHT == key) {
			spdlog::info("Right key pressed");
			mCenter.x += 1;
		}
		else if (KeyboardCodes::KEY_LEFT == key) {
			spdlog::info("Left key pressed");
			mCenter.x -= 1;
		}
	}
}
