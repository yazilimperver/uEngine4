#include "sdl_application.h"

#include <chrono>

#include <Gl/glew.h>
#include <GL/GL.h>

#include <SDL.h>

#include "spdlog/spdlog.h"

#include "time/sleep_util.h"

#include "application_base/client_graphic_application.h"

using namespace std::chrono;

void SdlApplication::Start() {

    Initialize();

    if (nullptr != mClientGraphicalApplication) {
        mClientGraphicalApplication->Initialize(*this);
    }
    /*
    // FPS Ticker
    mFPSTicker.AssignTickableApp(this);
    mFPSTicker.EnableReporting();
    mFPSTicker.Execute();
    */
    /*
    // Periodic ticker
    mPeriodicTicker.AssignTickableApp(this);
    mPeriodicTicker.Execute(100.0);
    */
    // SDL ticker
    mSdlTicker.AssignTickableApp(this);
    mSdlTicker.Execute(60);

    spdlog::info("SDL application stopped!");
}

void SdlApplication::Stop() {

    spdlog::info("SDL application execution stop command initiated!");
    mIsAppActive.store(false);
}

void SdlApplication::Input(double intervalInMsec) {
    HandleSDLEvents();
}

void SdlApplication::Update(double intervalInMsec) {
    spdlog::info("Tick time interval {:0.3f} msec", intervalInMsec); 
    
    if (nullptr != mClientGraphicalApplication) {
        mClientGraphicalApplication->Update(intervalInMsec);
    }
}

void SdlApplication::Display(double intervalInMsec) {
    // Perform display operation
    if (nullptr != mClientGraphicalApplication) {
        // Provide this time for interpolation
        mClientGraphicalApplication->Display(intervalInMsec);
    }
    
    if (mIsGlEnabled){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 1.0f, 1.f);
        SDL_GL_SwapWindow(mWindow);
    }
    else {
        SDL_RenderPresent(mRenderer);
    }
}