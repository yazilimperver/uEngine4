#include "sdl_application.h"

#include <chrono>

#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL.h>

#include "spdlog/spdlog.h"

#include "time/sleep_util.h"

#include "application_base/client_graphic_application.h"

#include "asset/asset_repository.h"

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
    mSdlTicker.StopTicker();
}

void SdlApplication::Input(double intervalInMsec) {
    HandleSDLEvents();
}

void SdlApplication::Update(double intervalInMsec) {
    //spdlog::info("Tick time interval {:0.3f} msec", intervalInMsec); 
    if (nullptr != mClientGraphicalApplicationToBeUsed) {

        if (nullptr != mClientGraphicalApplication)
            mClientGraphicalApplication->Finalize();
     
        mClientGraphicalApplication = mClientGraphicalApplicationToBeUsed;
        mClientGraphicalApplication->Initialize(*this);
        mClientGraphicalApplicationToBeUsed = nullptr;
    }

    if (nullptr != mClientGraphicalApplication) {
        mClientGraphicalApplication->Update(intervalInMsec);
    }
}

void SdlApplication::Display(double intervalInMsec) {
    if (mSdlParameters.IsGLEnabled) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // Perform display operation
    if (nullptr != mClientGraphicalApplication) {
        // Provide this time for interpolation
        mClientGraphicalApplication->Display(intervalInMsec);
    }
    
    if (mSdlParameters.IsGLEnabled){
        SDL_GL_SwapWindow(mWindow);
    }
    else {
        SDL_RenderPresent(mRenderer);
    }
}