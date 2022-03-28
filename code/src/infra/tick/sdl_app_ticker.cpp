#include "sdl_app_ticker.h"

#include <chrono>

#include "spdlog/spdlog.h"

using namespace std::chrono;

void SdlAppTicker::Execute(int32_t targetFps) {
    if (nullptr == mTickableApp) {
        spdlog::error("No tickable app is registered!");
        return;
    }
    if (mIsTickerActive.is_lock_free()) {
        spdlog::info("Ticker control flag is not atomic, check it!");
    }

    spdlog::info("Tick time interval {:0.3f} msec", 1.0/targetFps * 1000.0);

    mTickData.TickPerSeconds = targetFps;
    mTickData.SkipTicks = 1000 / mTickData.TickPerSeconds;
    mTickData.MaxFrameCountToSkip = 5; 
    
    high_resolution_clock::time_point currentTime;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    double elapsedInMsec{ 0.0 };

    while (true == mIsTickerActive.load()) {
        int32_t loopCount{ 0 };
        double interpolation{ 0.0 };
        auto nextGameTick = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();

        currentTime = high_resolution_clock::now();
        elapsedInMsec = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count()) * 0.000001;
        previousTime = currentTime;

       // Girdi tetikleyici
        mTickableApp->Input(elapsedInMsec);

        while ((time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count() > nextGameTick)
            &&
            (loopCount < mTickData.MaxFrameCountToSkip)) {

            // Guncelleme tetikleyici
            mTickableApp->Update(elapsedInMsec);

            nextGameTick += mTickData.SkipTicks;
            loopCount++;
        }

        static int incrementAmount = 1;

        if (loopCount >= mTickData.MaxFrameCountToSkip) {
            spdlog::warn("Not enough time for rendering or rendering take too much time check tasks! The last measured rendering time is: {}", incrementAmount);
        }

        interpolation = static_cast<double>(time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count()
            + mTickData.SkipTicks - nextGameTick) / static_cast<double>(mTickData.SkipTicks);

        // Goruntuleme tetikleyici
        mTickableApp->Display(elapsedInMsec);
    }
}

void SdlAppTicker::AssignTickableApp(GraphicalTickable* app){
	mTickableApp = app;
}

const TickData& SdlAppTicker::GetTickData() const {
    return mTickData;
}

void SdlAppTicker::StopTicker() {
    mIsTickerActive.store(false);
}
