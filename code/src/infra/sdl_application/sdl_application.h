#pragma once

#include <cstdint>
#include <vector>
#include <atomic>

#include "application_base/application_base.h"
#include "application_base/window_parameter.h"

#include "time/fps_timer.h"

#include "tick/tickable.h"
#include "tick/fps_ticker.h"
#include "tick/periodic_ticker.h"
#include "tick/sdl_app_ticker.h"
#include "tick/graphical_tickable.h"

#include "sdl_gamepad_controller.h"
#include "sdl_gamecontroller.h"
#include "sdl_touch_service.h"

struct SDL_Window;
struct SDL_Renderer;

class KeyboardEventListener;
class MouseEventListener;
class MouseMoveEventListener;
class GamepadEventListener;
class TouchEventHandler;
class ClientGraphicApplication;

struct uGamepadButtonData;
struct uGamepadAxisData;
class uIGraphicalApplication;

class SdlApplication
    : public ApplicationBase, public GraphicalTickable {
public:
    virtual void Start() override;
    virtual void Stop() override;

    void RegisterEventListener(KeyboardEventListener* listener);
    void RegisterEventListener(MouseEventListener* listener);
    void RegisterEventListener(MouseMoveEventListener* listener);
    void RegisterEventListener(GamepadEventListener* listener);
    void RegisterEventListener(TouchEventHandler* listener);
    
    void SetTitle(const std::string& title);

    WindowParameter& GetWindowParametrs();

    // SDL yardimcilari
    SDL_Renderer* GetSdlRenderer();
    SDL_Window* GetSdlWindow();
protected:
    //! An upper bound is given for update (i.e. multiple updates per tick and one display)
    //! Constant Game Speed independent of Variable FPS
    //! For more details check https://gafferongames.com/post/fix_your_timestep/ and http://gameprogrammingpatterns.com/game-loop.html
    //! For best information: http://www.yazilimperver.com/index.php/2017/12/09/oyun-donguleri/
    virtual bool Initialize() override;
    //virtual uErrorCode PostInitialize() override;
    virtual void Finalize() override;
    virtual void Input(double intervalInMsec);
    virtual void Update(double intervalInMsec);
    virtual void Display(double intervalInMsec);

    //! Handle SDL events
    void HandleSDLEvents();

    //! Parse windows parameters
    void ParseWindowParameters();

    //! Full screen switch
    void SetFullScreen(bool isFullscreen);

    //! Initialize SDL
    bool InitializeSDL();

    //! Initialize window settings
    void InitializeWindows();

    // Initialize opengl settings
    bool InitializeOpenGL();

    //! The client application
    std::shared_ptr<ClientGraphicApplication> mClientGraphicalApplication{ nullptr };

    //! The status of application
    bool mIsApplicationActive = true;

	//! Ignore back space exit in case of android
	bool mIgnoreExitWithBackButton = true;

    //! The SDL touch service API wrapper
    SdlTouchService mTouchService;

    bool mIsGlEnabled{ false };

    //! The SDL opengl context
    void* mMainGLContext;

    //! The SDL window reference
    SDL_Window* mWindow = nullptr;

    //! The sdl renderer object
    SDL_Renderer* mRenderer = nullptr;

    //! Event listeners
    std::vector<KeyboardEventListener*>  mKeyboardEventListeners;
    std::vector<MouseEventListener*>     mMouseEventListeners;
    std::vector<MouseMoveEventListener*> mMouseMoveEventListeners;
    std::vector<TouchEventHandler*>      mTouchEventListeners;

    //! Gamepad controller
    SdlGamepadController mGamepadController;

    //! The sdl window parameters
    SdlParameters mSDLParameters;

    //! Window parameters
    WindowParameter mWindowParameters;

    std::atomic<bool> mIsAppActive{ true };

    FpsTicker mFpsTicker;
    SdlAppTicker mSdlTicker;
    PeriodicTicker mPeriodicTicker;
};