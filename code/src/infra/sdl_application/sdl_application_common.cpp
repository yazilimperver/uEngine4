#include "sdl_application.h"

#include <chrono>

#include <Gl/glew.h>
#include <GL/GL.h>
#include <SDL.h>

#include "spdlog/spdlog.h"

#include "application_base/window_parameter.h"
#include "application_base/input_actions.h"
#include "application_base/keyboard_codes.h"
#include "application_base/keyboard_modifiers.h"
#include "application_base/mouse_buttons.h"
#include "application_base/gamepad_data.h"
#include "application_base/touch_action.h"
#include "application_base/touch_data.h"
#include "application_base/keyboard_event_listener.h"
#include "application_base/mouse_move_event_listener.h"
#include "application_base/mouse_event_listener.h"
#include "application_base/gamepad_event_listener.h"
#include "application_base/touch_event_handler.h"
#include "application_base/window_parameter_serializer.h"

#include "utility/json_data_parser.h"

using namespace std::chrono;

KeyboardCodes ConvertSDLKeyCodes(SDL_Scancode input);
KeyboardModifier ConvertSDLKeyModifierCodes(int16_t input);
    
bool SdlApplication::Initialize() {
    spdlog::info("SDL Application initialization started!");

    bool result{ false };

    // Default windows parameters
//    mWindowParameters.ClearColor = Color{ 255, 255, 255, 255 };
    mWindowParameters.Width = 640;
    mWindowParameters.Height = 480;
    mWindowParameters.IsFullScreen = false;
    mWindowParameters.IsVSYNCEnabled = false;
    mWindowParameters.Left = 100;
    mWindowParameters.Top = 100;

    result = this->InitializeSDL();
    
    spdlog::info("SDL Application initialization completed!");

    return result;
}

void SdlApplication::Finalize() {
    mKeyboardEventListeners.clear();
    mMouseEventListeners.clear();
    mMouseMoveEventListeners.clear();

    if (mIsGlEnabled) {
        SDL_GL_DeleteContext(mMainGLContext);
    }
    else {
        SDL_DestroyRenderer(mRenderer);
    }
    SDL_DestroyWindow(mWindow);
    SDL_Quit();

    return;
}

void SdlApplication::ParseWindowParameters(){
    JsonDataParser<WindowParameter> wpParser;

    auto opResult = wpParser.Deserialize("sdl_application_configuration.json");

    if (true == opResult.has_value())    {
        mWindowParameters = opResult.value();
    }
    else    {
        // hata durumlarina bakalim sonra
    }
}

bool SdlApplication::InitializeSDL() {
    bool status{ false };

    spdlog::info("SDL initialization started!");
    
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)  {
        spdlog::error("Initialization is failed! Error: {}\n", SDL_GetError());
        return status;
    }

    mGamepadController.Initialize();

    mSDLParameters.IsDisplayEventLogs = false;
    mSDLParameters.MajorVersion = 3;
    mSDLParameters.MinorVersion = 2;

    this->InitializeWindows();

    if (nullptr != mWindow) {
        spdlog::info("SDL Initialization is succeeded!\n");

        if (mIsGlEnabled) {
            status = this->InitializeOpenGL();

            // Vsync settings
            if (true == status) {
                spdlog::info("OpenGL initialization is successful!\n");

                if (true == mWindowParameters.IsVSYNCEnabled) {
                    SDL_GL_SetSwapInterval(1);
                }
                else {
                    SDL_GL_SetSwapInterval(0);
                }
            }
            else {
                spdlog::error("OpenGL initialization is failed. Error code: {}\n", status);
            }
        }
        else {

            // Create renderer for window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

            if (mRenderer) {
                status = true;
            }
        }
    }

    return status;
}

void SdlApplication::InitializeWindows() {
    if (mIsGlEnabled) {
        mSDLParameters.IsDisplayEventLogs = false;
        mSDLParameters.MajorVersion = 1;
        mSDLParameters.MinorVersion = 2;

        // Request opengl context
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Turn on double buffering with a 24bit Z buffer.
        // May need to change this to 16 or 32
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Create sdl window
        mWindow = SDL_CreateWindow(mWindowParameters.Title.c_str(),
            mWindowParameters.Left, mWindowParameters.Top,
            mWindowParameters.Width, mWindowParameters.Height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    }
    else {
        // Create sdl window
        mWindow = SDL_CreateWindow(mWindowParameters.Title.c_str(),
            mWindowParameters.Left, mWindowParameters.Top,
            mWindowParameters.Width, mWindowParameters.Height,
            SDL_WINDOW_SHOWN);
    }

    // TODO: Cursor hide mechanism
    // SDL_ShowCursor(SDL_DISABLE);

    if (nullptr == mWindow) {
        spdlog::error("SDL_CreateWindow failed! Error: {}", SDL_GetError());
    }
}

bool SdlApplication::InitializeOpenGL()
{
    bool status = false;

    mMainGLContext = SDL_GL_CreateContext(mWindow);

    // Initialize glew
    GLenum rev;
    glewExperimental = GL_TRUE;
    rev = glewInit();

    if (GLEW_OK != rev) {
        spdlog::error("GLEW init error. Error: {}\n", glewGetErrorString(rev));
    }
    else {
        status = true;
        spdlog::info("GLEW Init: Success!\n");
    }

    if (glewIsSupported("GL_VERSION_2_0")) {
        spdlog::info("Ready for OpenGL 2.0\n");
    }
    else {
        spdlog::error("OpenGL 2.0 not supported\n");
        status = false;
    }

    const GLubyte* str = glGetString(GL_VERSION);
    spdlog::info("GL Version: {}\n", str);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(mWindowParameters.ClearColor.R,
        mWindowParameters.ClearColor.G,
        mWindowParameters.ClearColor.B,
        mWindowParameters.ClearColor.A);
    return status;
}

void SdlApplication::HandleSDLEvents() {
    // Event handler
    SDL_Event e;

    // input action
    InputActions inputAction;
    KeyboardCodes keyCode;
    KeyboardModifier keyboardModifier;
    MouseButtons mouseButton;
    TouchAction touchAction;
    TouchData touchData;

    uint16_t mouseX = 0U;
    uint16_t mouseY = 0U;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            //Touch down
        case SDL_FINGERDOWN: {
            touchAction = TouchAction::FingerDown;
            touchData.Timestamp = e.tfinger.timestamp;
            touchData.DX = e.tfinger.dx;
            touchData.DY = e.tfinger.dy;
            touchData.X = e.tfinger.x;
            touchData.Y = e.tfinger.y;
            touchData.FingerId = e.tfinger.fingerId;
            touchData.TouchDeviceId = e.tfinger.touchId;
            touchData.Pressure = e.tfinger.pressure;

            // Inform listeners
            for (auto& listener : mTouchEventListeners) {
                listener->TouchEvent(touchAction, touchData);
            }
        }
        break;

        //Touch up
        case SDL_FINGERUP:
        {
            touchAction = TouchAction::FingerUp;
            touchData.Timestamp = e.tfinger.timestamp;
            touchData.DX = e.tfinger.dx;
            touchData.DY = e.tfinger.dy;
            touchData.X = e.tfinger.x;
            touchData.Y = e.tfinger.y;
            touchData.FingerId = e.tfinger.fingerId;
            touchData.TouchDeviceId = e.tfinger.touchId;
            touchData.Pressure = e.tfinger.pressure;

            // Inform listeners
            for (auto& listener : mTouchEventListeners)
            {
                listener->TouchEvent(touchAction, touchData);
            }
        }
        break;

        //Touch motion
        case SDL_FINGERMOTION:
        {
            touchAction = TouchAction::FingerMotion;
            touchData.Timestamp = e.tfinger.timestamp;
            touchData.DX = e.tfinger.dx;
            touchData.DY = e.tfinger.dy;
            touchData.X = e.tfinger.x;
            touchData.Y = e.tfinger.y;
            touchData.FingerId = e.tfinger.fingerId;
            touchData.TouchDeviceId = e.tfinger.touchId;
            touchData.Pressure = e.tfinger.pressure;

            // Inform listeners
            for (auto& listener : mTouchEventListeners)
            {
                listener->TouchEvent(touchAction, touchData);
            }
        }
        break;
        //multi gesture
        case SDL_MULTIGESTURE:
        {
            touchAction = TouchAction::MultiGesture;
            touchData.Timestamp = e.mgesture.timestamp;
            touchData.FingerCount = e.mgesture.numFingers;
            touchData.X = e.mgesture.x;
            touchData.Y = e.mgesture.y;
            touchData.TouchDeviceId = e.mgesture.touchId;
            touchData.ThetaInRadian = e.mgesture.dTheta;
            touchData.DDist = e.mgesture.dDist;

            // Inform listeners
            for (auto& listener : mTouchEventListeners)
            {
                listener->TouchEvent(touchAction, touchData);
            }
        }
        break;
            // User requests quit
        case SDL_QUIT:
        {
            //ConsoleLogger::Info("[SdlApplication] Quit Event Is Received\r\n");
            mIsApplicationActive = false;
        }
        break;
        // User presses a key
        case SDL_KEYDOWN:
        {
            keyboardModifier = ConvertSDLKeyModifierCodes(e.key.keysym.mod);
            inputAction = InputActions::PressAction;
            keyCode = ConvertSDLKeyCodes(e.key.keysym.scancode);

            if (keyCode == KeyboardCodes::KEY_F1)
            {
                this->SetFullScreen(true);
            }
            else if (keyCode == KeyboardCodes::KEY_F2)
            {
                this->SetFullScreen(false);
            }
#ifdef PLUGIN_MONITORING_SHORTCUTS_ENABLED
            else if (keyCode == KeyboardCodes::KEY_F3)
            {
                this->PrintActivePlugins();
            }
#endif
            if (keyCode == KeyboardCodes::KEY_Q
                || keyCode == KeyboardCodes::KEY_ESCAPE)
            {

                //ConsoleLogger::Info("[SdlApplication] Q or Esc is pressed!\r\n");
                mIsApplicationActive = false;
            }
									   
			if (e.key.keysym.sym == SDLK_AC_BACK)
			{
				if (false == mIgnoreExitWithBackButton)
				{
					//ConsoleLogger::Info("[SdlApplication] Q or Esc is pressed!\r\n");
					mIsApplicationActive = false;
				}
				else
				{
					keyCode = KeyboardCodes::KEY_ESCAPE;
				}
			}

            // Inform listeners
            for (auto& listener : mKeyboardEventListeners)
            {
                listener->KeyboardEvent(keyCode, e.key.keysym.scancode, inputAction, keyboardModifier);
            }
        }
        break;
        // User releases a key
        case SDL_KEYUP:
        {
            //Pass event to clients
            keyboardModifier = ConvertSDLKeyModifierCodes(e.key.keysym.mod);
            inputAction = InputActions::ReleaseAction;
            keyCode = ConvertSDLKeyCodes(e.key.keysym.scancode);

            // Inform listeners
            for (auto& listener : mKeyboardEventListeners)
            {
                listener->KeyboardEvent(keyCode, e.key.keysym.scancode, inputAction, keyboardModifier);
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
        {
            if (SDL_BUTTON_LEFT == e.button.button)
            {
                mouseButton = MouseButtons::MouseButtonLeft;
            }
            else if (SDL_BUTTON_RIGHT == e.button.button)
            {
                mouseButton = MouseButtons::MouseButtonRight;
            }
            else if (SDL_BUTTON_MIDDLE == e.button.button)
            {
                mouseButton = MouseButtons::MouseButtonMiddle;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                inputAction = InputActions::PressAction;
            }
            else
            {
                inputAction = InputActions::ReleaseAction;
            }

            // FTODO: Modifier
            // Inform listeners
            for (auto& listener : mMouseEventListeners)
            {
                listener->MouseButtonEvent(mouseButton, inputAction, 0, e.button.x, e.button.y);
            }
        }
        break;
        case SDL_MOUSEMOTION:
        {
            mouseX = e.motion.x;
            mouseY = e.motion.y;

            // Inform listeners
            for (auto& listener : mMouseMoveEventListeners)
            {
                listener->MouseMoveEvent(mouseX, mouseY);
            }
        }
        break;
        case SDL_CONTROLLERDEVICEADDED:
        {
            break;
        }

        case SDL_CONTROLLERDEVICEREMOVED:
        {
            mGamepadController.GamepadControllerDeviceAdded(e);
        }
        break;
        // Handle axis events
        case SDL_CONTROLLERAXISMOTION:
        {
            mGamepadController.GamepadControllerAxisMotion(e);
        }
        break;

        // Handle button events
        case SDL_CONTROLLERBUTTONUP:
        {
            mGamepadController.GamepadControllerButtonUp(e);
        }
        break;

        case SDL_CONTROLLERBUTTONDOWN:
        {
            mGamepadController.GamepadControllerButtonDown(e);
        }
        break;
        default:
            break;
        }
    }
}

void SdlApplication::RegisterEventListener(KeyboardEventListener* listener) {
    mKeyboardEventListeners.push_back(listener);
}

void SdlApplication::RegisterEventListener(MouseEventListener* listener) {
    mMouseEventListeners.push_back(listener);
}

void SdlApplication::RegisterEventListener(MouseMoveEventListener* listener) {
    mMouseMoveEventListeners.push_back(listener);
}

void SdlApplication::RegisterEventListener(GamepadEventListener* listener) {
    mGamepadController.RegisterEventListener(listener);
}

void SdlApplication::RegisterEventListener(TouchEventHandler* listener) {
    mTouchEventListeners.push_back(listener);
    listener->Initialize(&mTouchService);
}

void SdlApplication::SetTitle(const std::string& title) {
    if (nullptr != mWindow)
    {
        SDL_SetWindowTitle(mWindow, title.c_str());
    }
}

SDL_Renderer* SdlApplication::GetSdlRenderer() {
    return mRenderer;
}

SDL_Window* SdlApplication::GetSdlWindow() {
    return mWindow;
}

WindowParameter& SdlApplication::GetWindowParametrs() {
    return mWindowParameters;
}

void SdlApplication::SetFullScreen(bool isFullscreen) {
    if (true == isFullscreen)    {
        SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
    }
    else    {
        SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
    }
}

KeyboardModifier ConvertSDLKeyModifierCodes(int16_t input) {
    uint32_t keyboardModifier = 0U;

    // Determine mod keyboards
    if (input & KMOD_LCTRL)    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_LCTRL);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_CTRL);
    }
    if (input & KMOD_RCTRL)
    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_RCTRL);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_CTRL);
    }
    if (input & KMOD_RSHIFT)
    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_RSHIFT);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_SHIFT);

    }
    if (input & KMOD_LSHIFT)
    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_LSHIFT);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_SHIFT);
    }
    if (input & KMOD_RALT)
    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_RALT);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_ALT);
    }
    if (input & KMOD_LALT)
    {
        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_LALT);

        keyboardModifier
            |= static_cast<uint32_t>(KeyboardModifier::KMOD_ALT);
    }

    return static_cast<KeyboardModifier>(keyboardModifier);
}

KeyboardCodes ConvertSDLKeyCodes(SDL_Scancode input)
{
    switch (input)
    {
    case SDL_SCANCODE_UNKNOWN:
        return KeyboardCodes::KEY_UNKNOWN;
    case SDL_SCANCODE_A:
        return KeyboardCodes::KEY_A;
    case SDL_SCANCODE_B:
        return KeyboardCodes::KEY_B;
    case SDL_SCANCODE_C:
        return KeyboardCodes::KEY_C;
    case SDL_SCANCODE_D:
        return KeyboardCodes::KEY_D;
    case SDL_SCANCODE_E:
        return KeyboardCodes::KEY_E;
    case SDL_SCANCODE_F:
        return KeyboardCodes::KEY_F;
    case SDL_SCANCODE_G:
        return KeyboardCodes::KEY_G;
    case SDL_SCANCODE_H:
        return KeyboardCodes::KEY_H;
    case SDL_SCANCODE_I:
        return KeyboardCodes::KEY_I;
    case SDL_SCANCODE_J:
        return KeyboardCodes::KEY_J;
    case SDL_SCANCODE_K:
        return KeyboardCodes::KEY_K;
    case SDL_SCANCODE_L:
        return KeyboardCodes::KEY_L;
    case SDL_SCANCODE_M:
        return KeyboardCodes::KEY_M;
    case SDL_SCANCODE_N:
        return KeyboardCodes::KEY_N;
    case SDL_SCANCODE_O:
        return KeyboardCodes::KEY_O;
    case SDL_SCANCODE_P:
        return KeyboardCodes::KEY_P;
    case SDL_SCANCODE_Q:
        return KeyboardCodes::KEY_Q;
    case SDL_SCANCODE_R:
        return KeyboardCodes::KEY_R;
    case SDL_SCANCODE_S:
        return KeyboardCodes::KEY_S;
    case SDL_SCANCODE_T:
        return KeyboardCodes::KEY_T;
    case SDL_SCANCODE_U:
        return KeyboardCodes::KEY_U;
    case SDL_SCANCODE_V:
        return KeyboardCodes::KEY_V;
    case SDL_SCANCODE_W:
        return KeyboardCodes::KEY_W;
    case SDL_SCANCODE_X:
        return KeyboardCodes::KEY_X;
    case SDL_SCANCODE_Y:
        return KeyboardCodes::KEY_Y;
    case SDL_SCANCODE_Z:
        return KeyboardCodes::KEY_Z;
    case SDL_SCANCODE_1:
        return KeyboardCodes::KEY_1;
    case SDL_SCANCODE_2:
        return KeyboardCodes::KEY_2;
    case SDL_SCANCODE_3:
        return KeyboardCodes::KEY_3;
    case SDL_SCANCODE_4:
        return KeyboardCodes::KEY_4;
    case SDL_SCANCODE_5:
        return KeyboardCodes::KEY_5;
    case SDL_SCANCODE_6:
        return KeyboardCodes::KEY_6;
    case SDL_SCANCODE_7:
        return KeyboardCodes::KEY_7;
    case SDL_SCANCODE_8:
        return KeyboardCodes::KEY_8;
    case SDL_SCANCODE_9:
        return KeyboardCodes::KEY_9;
    case SDL_SCANCODE_0:
        return KeyboardCodes::KEY_0;
    case SDL_SCANCODE_RETURN:
        return KeyboardCodes::KEY_ENTER;
    case SDL_SCANCODE_ESCAPE:
        return KeyboardCodes::KEY_ESCAPE;
    case SDL_SCANCODE_BACKSPACE:
        return KeyboardCodes::KEY_BACKSPACE;
    case SDL_SCANCODE_TAB:
        return KeyboardCodes::KEY_TAB;
    case SDL_SCANCODE_SPACE:
        return KeyboardCodes::KEY_SPACE;
    case SDL_SCANCODE_MINUS:
        return KeyboardCodes::KEY_MINUS;
    case SDL_SCANCODE_EQUALS:
        return KeyboardCodes::KEY_EQUAL;
    case SDL_SCANCODE_LEFTBRACKET:
        return KeyboardCodes::KEY_LEFT_BRACKET;
    case SDL_SCANCODE_RIGHTBRACKET:
        return KeyboardCodes::KEY_RIGHT_BRACKET;
    case SDL_SCANCODE_BACKSLASH:
        return KeyboardCodes::KEY_BACKSLASH;
    case SDL_SCANCODE_SEMICOLON:
        return KeyboardCodes::KEY_SEMICOLON;
    case SDL_SCANCODE_APOSTROPHE:
        return KeyboardCodes::KEY_APOSTROPHE;
    case SDL_SCANCODE_GRAVE:
        return KeyboardCodes::KEY_GRAVE_ACCENT;
    case SDL_SCANCODE_COMMA:
        return KeyboardCodes::KEY_COMMA;
    case SDL_SCANCODE_PERIOD:
        return KeyboardCodes::KEY_PERIOD;
    case SDL_SCANCODE_SLASH:
        return KeyboardCodes::KEY_SLASH;
    case SDL_SCANCODE_CAPSLOCK:
        return KeyboardCodes::KEY_CAPS_LOCK;
    case SDL_SCANCODE_F1:
        return KeyboardCodes::KEY_F1;
    case SDL_SCANCODE_F2:
        return KeyboardCodes::KEY_F2;
    case SDL_SCANCODE_F3:
        return KeyboardCodes::KEY_F3;
    case SDL_SCANCODE_F4:
        return KeyboardCodes::KEY_F4;
    case SDL_SCANCODE_F5:
        return KeyboardCodes::KEY_F5;
    case SDL_SCANCODE_F6:
        return KeyboardCodes::KEY_F6;
    case SDL_SCANCODE_F7:
        return KeyboardCodes::KEY_F7;
    case SDL_SCANCODE_F8:
        return KeyboardCodes::KEY_F8;
    case SDL_SCANCODE_F9:
        return KeyboardCodes::KEY_F9;
    case SDL_SCANCODE_F10:
        return KeyboardCodes::KEY_F10;
    case SDL_SCANCODE_F11:
        return KeyboardCodes::KEY_F11;
    case SDL_SCANCODE_F12:
        return KeyboardCodes::KEY_F12;
    case SDL_SCANCODE_PRINTSCREEN:
        return KeyboardCodes::KEY_PRINT_SCREEN;
    case SDL_SCANCODE_SCROLLLOCK:
        return KeyboardCodes::KEY_SCROLL_LOCK;
    case SDL_SCANCODE_PAUSE:
        return KeyboardCodes::KEY_PAUSE;
    case SDL_SCANCODE_INSERT:
        return KeyboardCodes::KEY_INSERT;
    case SDL_SCANCODE_HOME:
        return KeyboardCodes::KEY_HOME;
    case SDL_SCANCODE_PAGEUP:
        return KeyboardCodes::KEY_PAGE_UP;
    case SDL_SCANCODE_DELETE:
        return KeyboardCodes::KEY_DELETE;
    case SDL_SCANCODE_END:
        return KeyboardCodes::KEY_END;
    case SDL_SCANCODE_PAGEDOWN:
        return KeyboardCodes::KEY_PAGE_DOWN;
    case SDL_SCANCODE_RIGHT:
        return KeyboardCodes::KEY_RIGHT;
    case SDL_SCANCODE_LEFT:
        return KeyboardCodes::KEY_LEFT;
    case SDL_SCANCODE_DOWN:
        return KeyboardCodes::KEY_DOWN;
    case SDL_SCANCODE_UP:
        return KeyboardCodes::KEY_UP;
    case SDL_SCANCODE_KP_DIVIDE:
        return KeyboardCodes::KEY_KP_DIVIDE;
    case SDL_SCANCODE_KP_MULTIPLY:
        return KeyboardCodes::KEY_KP_MULTIPLY;
    case SDL_SCANCODE_KP_MINUS:
        return KeyboardCodes::KEY_KP_SUBTRACT;
    case SDL_SCANCODE_KP_PLUS:
        return KeyboardCodes::KEY_KP_ADD;
    case SDL_SCANCODE_KP_ENTER:
        return KeyboardCodes::KEY_KP_ENTER;
    case SDL_SCANCODE_KP_1:
        return KeyboardCodes::KEY_KP_1;
    case SDL_SCANCODE_KP_2:
        return KeyboardCodes::KEY_KP_2;
    case SDL_SCANCODE_KP_3:
        return KeyboardCodes::KEY_KP_3;
    case SDL_SCANCODE_KP_4:
        return KeyboardCodes::KEY_KP_4;
    case SDL_SCANCODE_KP_5:
        return KeyboardCodes::KEY_KP_5;
    case SDL_SCANCODE_KP_6:
        return KeyboardCodes::KEY_KP_6;
    case SDL_SCANCODE_KP_7:
        return KeyboardCodes::KEY_KP_7;
    case SDL_SCANCODE_KP_8:
        return KeyboardCodes::KEY_KP_8;
    case SDL_SCANCODE_KP_9:
        return KeyboardCodes::KEY_KP_9;
    case SDL_SCANCODE_KP_0:
        return KeyboardCodes::KEY_KP_0;
    case SDL_SCANCODE_KP_PERIOD:
        return KeyboardCodes::KEY_PERIOD;
    case SDL_SCANCODE_KP_EQUALS:
        return KeyboardCodes::KEY_KP_EQUAL;
    case SDL_SCANCODE_F13:
        return KeyboardCodes::KEY_F13;
    case SDL_SCANCODE_F14:
        return KeyboardCodes::KEY_F14;
    case SDL_SCANCODE_F15:
        return KeyboardCodes::KEY_F15;
    case SDL_SCANCODE_F16:
        return KeyboardCodes::KEY_F16;
    case SDL_SCANCODE_F17:
        return KeyboardCodes::KEY_F17;
    case SDL_SCANCODE_F18:
        return KeyboardCodes::KEY_F18;
    case SDL_SCANCODE_F19:
        return KeyboardCodes::KEY_F19;
    case SDL_SCANCODE_F20:
        return KeyboardCodes::KEY_F20;
    case SDL_SCANCODE_F21:
        return KeyboardCodes::KEY_F21;
    case SDL_SCANCODE_F22:
        return KeyboardCodes::KEY_F22;
    case SDL_SCANCODE_F23:
        return KeyboardCodes::KEY_F23;
    case SDL_SCANCODE_F24:
        return KeyboardCodes::KEY_F24;
    case SDL_SCANCODE_MENU:
        return KeyboardCodes::KEY_MENU;
    case SDL_SCANCODE_KP_LEFTBRACE:
        return KeyboardCodes::KEY_LEFT_BRACKET;
    case SDL_SCANCODE_KP_RIGHTBRACE:
        return KeyboardCodes::KEY_RIGHT_BRACKET;
    case SDL_SCANCODE_KP_TAB:
        return KeyboardCodes::KEY_TAB;
    case SDL_SCANCODE_KP_BACKSPACE:
        return KeyboardCodes::KEY_BACKSPACE;
    case SDL_SCANCODE_LCTRL:
        return KeyboardCodes::KEY_LEFT_CONTROL;
    case SDL_SCANCODE_LSHIFT:
        return KeyboardCodes::KEY_LEFT_SHIFT;
    case SDL_SCANCODE_LALT:
        return KeyboardCodes::KEY_LEFT_ALT;
    case SDL_SCANCODE_RCTRL:
        return KeyboardCodes::KEY_RIGHT_CONTROL;
    case SDL_SCANCODE_RSHIFT:
        return KeyboardCodes::KEY_RIGHT_SHIFT;
    case SDL_SCANCODE_RALT:
        return KeyboardCodes::KEY_RIGHT_ALT;
    default:
        return KeyboardCodes::KEY_UNKNOWN;
    }
}