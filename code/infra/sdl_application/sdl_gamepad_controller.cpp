#include "sdl_gamepad_controller.h"
#include "application_base/gamepad_event_listener.h"
#include "application_base/input_actions.h"

#include "SDL.h"
#include "SDL_gamecontroller.h"

void SdlGamepadController::Initialize() {
    SDL_GameController *controller = nullptr;
    uint32_t numberOfGameControllers = SDL_NumJoysticks();

    for (uint32_t i = 0; i < numberOfGameControllers; i++)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            mControllers.push_back(controller);

           // uConsoleLogger::Info("[uSDLApplicationBase] %s.\r\n", SDL_GameControllerMapping(controller));
        }
    }

    // Enable controller event state
    SDL_GameControllerEventState(SDL_ENABLE);
}

uint32_t SdlGamepadController::GetGamepadControllerCount() {
    return static_cast<uint32_t>(mControllers.size());
}

std::string SdlGamepadController::GetGamepadControllerMapping(uint32_t index) {
    if (index < mControllers.size()) {
        return std::string(SDL_GameControllerMapping(mControllers[index]));
    }
    else {
        return std::string("");
    }
}

void SdlGamepadController::SetDeadzoneValue(uint32_t deadZone) {
    mDeadZone = deadZone;
}

uint32_t SdlGamepadController::GetDeadzoneValue() {
    return mDeadZone;
}

bool& SdlGamepadController::GetPollingGamepadControllerEnabledStatus() {
    return mIsPollingGamepadControllerEnabled;
}

void SdlGamepadController::GamepadControllerDeviceAdded(SDL_Event& e) {
    mIsPollingGamepadControllerEnabled = false;
    // receive the controller index given by SDL
    int32_t cIdx = e.cdevice.which;

    if (SDL_IsGameController(cIdx))     {
        SDL_GameController * controller = SDL_GameControllerOpen(cIdx);
        SDL_Joystick* j = SDL_GameControllerGetJoystick(controller);
        SDL_JoystickID joyId = SDL_JoystickInstanceID(j);

        auto itr = mControllers.begin();

        while (itr != mControllers.end()) {
            if (SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(*itr)) == joyId) {
                break;
            }
        }

        if (itr == mControllers.end()) {
            if (0 != controller) {
                // Save the joystick id to used in the future events
                mControllers.push_back(controller);

                // uConsoleLogger::Info("[uSDLApplicationBase] A new controller is added. Name is : %s\r\n", SDL_GameControllerName(controller));
                // uConsoleLogger::Info("[uSDLApplicationBase] A new controller is added. Mapping is : %s\r\n", SDL_GameControllerMapping(controller));

                std::string nameOfController(SDL_GameControllerName(controller));
                // Inform listeners
                for (auto& listener : mGamepadEventListeners) {
                    listener->GamepadControllerAdded(nameOfController, joyId);
                }
            }
        }
        else {
        }
    }
}

void SdlGamepadController::GamepadControllerAxisMotion(SDL_Event& e) {
    GamepadAxisData gamepadAxisData;
    int32_t controllerIndex = e.cdevice.which;
    this->PollGamepadAxisEvents(controllerIndex, gamepadAxisData);

    // Inform listeners
    for (auto& listener : mGamepadEventListeners)     {
        listener->GamepadEvent(controllerIndex, gamepadAxisData);
    }
}

void SdlGamepadController::GamepadControllerButtonDown(SDL_Event& e) {
    GamepadButtonData gamepadButtonData;
    int32_t controllerIndex = e.cdevice.which;
    this->PollGamepadButtons(controllerIndex, gamepadButtonData);

    for (auto& listener : mGamepadEventListeners) {
        listener->GamepadEvent(controllerIndex, InputActions::ReleaseAction, gamepadButtonData);
    }
}

void SdlGamepadController::GamepadControllerButtonUp(SDL_Event& e) {
    GamepadButtonData gamepadButtonData;
    int32_t controllerIndex = e.cdevice.which;
    this->PollGamepadButtons(controllerIndex, gamepadButtonData);

    for (auto& listener : mGamepadEventListeners) {
        listener->GamepadEvent(controllerIndex, InputActions::PressAction, gamepadButtonData);
    }
}

void SdlGamepadController::RegisterEventListener(GamepadEventListener* listener) {
    mGamepadEventListeners.push_back(listener);
}

void SdlGamepadController::PollGamepadButtons(int32_t index, GamepadButtonData& buttonData) {
    if (index < static_cast<int32_t>(mControllers.size())) {
        SDL_GameController* controller = mControllers[index];

        // Read Button States
        buttonData.mAButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
        buttonData.mBButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
        buttonData.mXButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
        buttonData.mYButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);


        // Read D-PAD Button States
        buttonData.mLeftDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        buttonData.mRightDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
        buttonData.mUpDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
        buttonData.mDownDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);

        // Read Menu Button States
        buttonData.mStartButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
        buttonData.mSelectButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
        buttonData.mGuideButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);

        // Read Analog Click Button States
        buttonData.mLeftStickButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
        buttonData.mRightStickButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);

        // Read Shoulder Button States
        buttonData.mLeftShoulderButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
        buttonData.mRightShoulderButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    }
}

void SdlGamepadController::PollGamepadAxisEvents(int32_t index, GamepadAxisData& axisData) {
    if (index < static_cast<int32_t>(mControllers.size())) {
        SDL_GameController* controller = mControllers[index];

        // Check if the joystick has digital triggers, like the Wii U Pro Controller, and
        // read the values.
        axisData.mLeftTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
        axisData.mRightTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

        // Read Analog Joystick Values
        axisData.mLeftXAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
        axisData.mLeftYAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
        axisData.mRightXAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
        axisData.mRightYAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
    }
}

void SdlGamepadController::PollGamepadControllers() {
    if (mControllers.size() > 0) {
        if (true == mIsPollingGamepadControllerEnabled) {
            // Update all connected controller states.
            SDL_GameControllerUpdate();

            for (auto* controller : mControllers) {
                // Check to see if sdlGamepad is actually connected. If it isn't this will terminate the
                // polling and initialize the event handling.
                if (SDL_FALSE == SDL_GameControllerGetAttached(controller)) {
                    mIsPollingGamepadControllerEnabled = true;
                }

                // Wait for connection
                if (true == mIsPollingGamepadControllerEnabled) {
                    return;
                }

                GamepadData gamepadData;

                // Read D-PAD Button States
                gamepadData.mButtonData.mLeftDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
                gamepadData.mButtonData.mRightDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
                gamepadData.mButtonData.mUpDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
                gamepadData.mButtonData.mDownDPAD = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);

                // Read Menu Button States
                gamepadData.mButtonData.mStartButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
                gamepadData.mButtonData.mSelectButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
                gamepadData.mButtonData.mGuideButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);

                // Read Analog Click Button States
                gamepadData.mButtonData.mLeftStickButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
                gamepadData.mButtonData.mRightStickButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);

                // Read Shoulder Button States
                gamepadData.mButtonData.mLeftShoulderButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
                gamepadData.mButtonData.mRightShoulderButton = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

                // Check if the joystick has digital triggers, like the Wii U Pro Controller, and
                // read the values.
                gamepadData.mAxisData.mLeftTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
                gamepadData.mAxisData.mRightTrigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

                // Read Analog Joystick Values
                gamepadData.mAxisData.mLeftXAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
                gamepadData.mAxisData.mLeftYAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
                gamepadData.mAxisData.mRightXAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
                gamepadData.mAxisData.mRightYAxis = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
            }
        }
    }
}