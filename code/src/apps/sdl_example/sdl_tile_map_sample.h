/**
 * @file sdl_tile_map_sample.h.
 * @date 21.05.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLTILEMAPSAMPLE_H_
#define SDLTILEMAPSAMPLE_H_

#include <memory>

#include "application_base/client_graphic_application.h"
#include "application_base/window_parameter.h"
#include "application_base/keyboard_event_listener.h"

#include "tile_map/tile_map.h"

struct SDL_Renderer;

class SdlTileMapSample
	: public ClientGraphicApplication, public KeyboardEventListener {
public:
	virtual void Initialize(SdlApplication& sdlApplication) override;
	virtual void Update(double tickTimeInMsec) override;
	virtual void Display(double tickTimeInMsec) override;
	virtual void Finalize() override;
protected:
	SDL_Renderer* mRenderer{ nullptr };
	WindowParameter mParameters;
	std::unique_ptr<basic_engine::TileMap> mSampleTileMap;

	virtual void KeyboardEvent(KeyboardCodes key, int32_t scancode, InputActions action, KeyboardModifier mods) override;
};

#endif // !SDLTILEMAPSAMPLE_H_
