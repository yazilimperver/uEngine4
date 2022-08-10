/**
 * @file sdl_gamepad_controller.h.
 * @date 9.08.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDL_GAMEPAD_CONTROLLER
#define SDL_GAMEPAD_CONTROLLER

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

#endif // !SDL_GAMEPAD_CONTROLLER

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
