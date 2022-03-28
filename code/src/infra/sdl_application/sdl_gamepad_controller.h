#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "sdl_parameters.h"

#include "application_base/gamepad_data.h"

union SDL_Event; 
struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

class GamepadEventListener;

class SdlGamepadController {
public:
    void Initialize();

    virtual uint32_t GetGamepadControllerCount();
    virtual std::string GetGamepadControllerMapping(uint32_t index);
    virtual void SetDeadzoneValue(uint32_t deadZone);
    virtual uint32_t GetDeadzoneValue();

    bool& GetPollingGamepadControllerEnabledStatus();
    void GamepadControllerDeviceAdded(SDL_Event& e);
    void GamepadControllerAxisMotion(SDL_Event& e);
    void GamepadControllerButtonDown(SDL_Event& e);
    void GamepadControllerButtonUp(SDL_Event& e);
    void RegisterEventListener(GamepadEventListener* listener);
protected:
    //! Poll game pad events
    void PollGamepadControllers();
    void PollGamepadButtons(int32_t index, GamepadButtonData& buttonData);
    void PollGamepadAxisEvents(int32_t index, GamepadAxisData& axisData);

    //! Gamepad event listeners
    std::vector<GamepadEventListener*>   mGamepadEventListeners;

    //! The detected controllers
    std::vector<SDL_GameController*> mControllers;

    //! Controller event handling
    bool mIsPollingGamepadControllerEnabled = true;

    //! Dead zone for controllers
    int32_t mDeadZone = 3200;
};