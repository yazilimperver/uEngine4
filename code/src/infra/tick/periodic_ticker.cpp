#include "periodic_ticker.h"

#include <chrono>

#include "spdlog/spdlog.h"

#include "time/sleep_util.h"

using namespace std::chrono;

void PeriodicTicker::AssignTickableApp(Tickable* app) {
    mTickableApp = app;
}

void PeriodicTicker::StopTicker() {
    mIsTickerActive.store(false);
}

void PeriodicTicker::Execute(double periodInMsec) {
    SetInterval(periodInMsec);

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

    spdlog::info("Periodic Ticker started!");

    while (true == mIsTickerActive.load()) {
        currentTime = high_resolution_clock::now();
        elapsedInMsec = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count()) * 0.000001;
        previousTime = currentTime;

        mTickableApp->Tick(elapsedInMsec);

        if (mPeriodicityInSec > 0.0) {
            SleepUtil::PreciseSleep(mPeriodicityInSec);
        }
    }

    spdlog::info("Periodic Ticker stopped!");
}

void PeriodicTicker::SetInterval(double periodInMsec) {
    mPeriodicityInSec = periodInMsec * 0.001;
}
