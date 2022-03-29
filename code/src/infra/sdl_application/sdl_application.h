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

#include "utility/parameter_set.h"

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
    void ParseSdlParameters();

    //! Full screen switch
    void SetFullScreen(bool isFullscreen);

    //! Initialize SDL
    bool InitializeSDL();

    //! Initialize window settings
    void InitializeWindows();

    // Initialize opengl settings
    bool InitializeOpenGL();

    /** @brief Ýstemci grafik uygulamasý */
    std::shared_ptr<ClientGraphicApplication> mClientGraphicalApplication{ nullptr };

	/** @brief Geri dugmesi ile cikilsin mi */
	bool mIgnoreExitWithBackButton = true;

    /** @brief SDL dokunma servisi */
    SdlTouchService mTouchService;

    /** @brief SDL OpenGL icin mi kullanilacak */
    bool mIsGlEnabled{ false };

    /** @brief SDL OpenGL context */
    void* mMainGLContext;

    /** @brief SDL penceresi */
    SDL_Window* mWindow{ nullptr };

    /** @brief SDL renderer */
    SDL_Renderer* mRenderer{ nullptr };

    /** @brief Olay dinleyicileri */
    std::vector<KeyboardEventListener*>  mKeyboardEventListeners;
    std::vector<MouseEventListener*>     mMouseEventListeners;
    std::vector<MouseMoveEventListener*> mMouseMoveEventListeners;
    std::vector<TouchEventHandler*>      mTouchEventListeners;

    /** @brief Gamepad kontrolcüsü */
    SdlGamepadController mGamepadController;

    /** @brief SDL parametreleri */
    SdlParameters mSdlParameters;

    /** @brief Pencere ayarlarý */
    WindowParameter mWindowParameters;

    /** @brief Uygulama aktif mi */
    std::atomic<bool> mIsAppActive{ true };

    /** @brief FPS ticker */
    FpsTicker mFpsTicker;

    /** @brief Varsayýlan SDL ticker */
    SdlAppTicker mSdlTicker;

    /** @brief Perioydik ticker */
    PeriodicTicker mPeriodicTicker;

    /** @brief Uygulama capinda paylasilacak olan ayarlar */
    ParameterSet mAppWiseSettings;
};