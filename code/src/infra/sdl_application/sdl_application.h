/**
 * @file sdl_application.h.
 * @date 17.04.2022
 * @author Yazilimperver
 * @brief
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef SDL_APPLICATION_H
#define SDL_APPLICATION_H

#include <cstdint>
#include <vector>
#include <atomic>
#include <memory>

#include "asset/asset_repository.h"

#include "application_base/application_base.h"
#include "application_base/window_parameter.h"
#include "application_base/client_graphic_application.h"

#include "time/fps_timer.h"

#include "tick/tickable.h"
#include "tick/fps_ticker.h"
#include "tick/periodic_ticker.h"
#include "tick/sdl_app_ticker.h"
#include "tick/graphical_tickable.h"

#include "utility/parameter_set.h"

#include "graphics/rectangle.h"

#include "sdl_gamepad_controller.h"
#include "sdl_touch_service.h"

struct SDL_Window;
struct SDL_Renderer;

class KeyboardEventListener;
class MouseEventListener;
class MouseMoveEventListener;
class MouseWheelEventListener;
class GamepadEventListener;
class TouchEventHandler;
class SDLEventListener;

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
    void RegisterEventListener(MouseWheelEventListener* listener);
    void RegisterEventListener(GamepadEventListener* listener);
    void RegisterEventListener(TouchEventHandler* listener);
    void RegisterEventListener(SDLEventListener* listener);
    
    void SetTitle(const std::string& title);

    WindowParameter& GetWindowParametrs();
    SdlParameters& GetSDLParameters();

    // SDL yardimcilari
    SDL_Renderer* GetSdlRenderer();
    SDL_Window* GetSdlWindow();
    void* GetGlContext();

    // Gosterim alanini donelim
    infra::Rectangle<int32_t>& GetViewport();

    // Mevcut grafik uygulamasini yenisi ile degistirmek icin kullanilacak fonksiyon
    void UpdateGraphicApplication(std::shared_ptr<ClientGraphicApplication> newApplication);

    infra::AssetService& AssetService();
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

    void HandleSDLEvents();
    void ParseWindowParameters();
    void ParseSdlParameters();
    void SetFullScreen(bool isFullscreen);

    bool InitializeSDL();
    void InitializeWindows();
    bool InitializeOpenGL();

    /** @brief �stemci grafik uygulamas� */
    std::shared_ptr<ClientGraphicApplication> mClientGraphicalApplication{ nullptr };
    std::shared_ptr<ClientGraphicApplication> mClientGraphicalApplicationToBeUsed{ nullptr };

	/** @brief Geri dugmesi ile cikilsin mi */
	bool mIgnoreExitWithBackButton = true;

    /** @brief SDL dokunma servisi */
    SdlTouchService mTouchService;

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
    std::vector<MouseWheelEventListener*> mMouseWheelEventListeners;
    std::vector<TouchEventHandler*>      mTouchEventListeners;
    std::vector<SDLEventListener*>       mSDLEventListeners;

    /** @brief Gamepad kontrolc�s� */
    SdlGamepadController mGamepadController;

    /** @brief SDL parametreleri */
    SdlParameters mSdlParameters;

    /** @brief Pencere ayarlar� */
    WindowParameter mWindowParameters;

    /** @brief Gosterim yapilan goruntuleme alani */
    infra::Rectangle<int32_t> mRenderViewport;

    /** @brief Uygulama aktif mi */
    std::atomic<bool> mIsAppActive{ true };

    /** @brief FPS ticker */
    FpsTicker mFpsTicker;

    /** @brief Varsay�lan SDL ticker */
    SdlAppTicker mSdlTicker;

    /** @brief Perioydik ticker */
    PeriodicTicker mPeriodicTicker;

    /** @brief Uygulama capinda paylasilacak olan ayarlar */
    ParameterSet mAppWiseSettings;

    /** @brief Uygulama tarafindan kullanilabilecek asset reposu */
    infra::AssetRepository mAssetRepository;
};

#endif // !SDL_APPLICATION_H

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
