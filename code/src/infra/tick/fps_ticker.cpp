#include "fps_ticker.h"

#include <chrono>

#include "spdlog/spdlog.h"

using namespace std::chrono;

void FpsTicker::Execute() {

    if (nullptr == mTickableApp) {
        spdlog::error("No tickable app is registered!");
        return;
    }
    if (mIsTickerActive.is_lock_free()) {
        spdlog::info("Ticker control flag is not atomic, check it!");
    }

    high_resolution_clock::time_point currentTime;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    double elapsedInMsec{ 0.0 };

    spdlog::info("FPS Ticker started!");

    while (true == mIsTickerActive.load()) {
        currentTime = high_resolution_clock::now();
        elapsedInMsec = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count()) * 0.000001;
        previousTime = currentTime;

        mTickableApp->Tick(elapsedInMsec);
        mFpsTimer.FPSCheck();
    }

    spdlog::info("FPS Ticker stopped!");
}

void FpsTicker::SetFPSParameters(double theTargetFps, uint32_t reportInterval) {
    mFpsTimer.SetFPSParameters(theTargetFps, reportInterval);
}

void FpsTicker::EnableReporting() {
    mFpsTimer.EnableReporting();
}

void FpsTicker::DisableReporting() {
    mFpsTimer.DisableReporting();
}

void FpsTicker::AssignTickableApp(Tickable* app) {
    mTickableApp = app;
}

void FpsTicker::StopTicker() {
    mIsTickerActive.store(false);
}
