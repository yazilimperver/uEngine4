#include "game_ticker.h"

#include <chrono>
#include <thread>

#include "spdlog/spdlog.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

void GameTicker::Execute(LoopPolicy loopPolicy) {
    mLoopPolicy = loopPolicy;
    if (nullptr == mTickableApp) {
        spdlog::error("No tickable app is registered!");
        return;
    }
    if (mIsTickerActive.is_lock_free()) {
        spdlog::info("Ticker control flag is not atomic, check it!");
    }

    switch (mLoopPolicy)    {
    case LoopPolicy::BruteForce:
        BruteForceLoop();
        break;
    case LoopPolicy::FixFps:
        FixFpsLoop();
        break;
    case LoopPolicy::VariableFps:
        VariableFpsLoop();
        break;
    case LoopPolicy::ConstGameSpeedWithMaxFps:
        ConstGameSpeedWithMaxFpsLoop();
        break;
    case LoopPolicy::FixGameSpeedVariableFps:
        FixGameSpeedVariableFpsLoop();
        break;
    default:
        break;
    }
}

void GameTicker::AssignTickableApp(GraphicalTickable* app) {
    mTickableApp = app;
}

void GameTicker::StopTicker() {
    mIsTickerActive.store(false);
}

constexpr int32_t cTicksPerSecond = 60;
constexpr int32_t cPerTickSkipTimeInMs = 1000 / cTicksPerSecond;
constexpr double  cPerTickSkipTimeInMsDbl = 1000.0 / cTicksPerSecond;
constexpr int32_t cMaxFrameskip = 5;

void GameTicker::BruteForceLoop() {
    spdlog::info("Brute force loop policy is selected and started!");

    auto previous(high_resolution_clock::now());
    time_point<high_resolution_clock> current;
    float elapsed;

    while (true == mIsTickerActive.load())     {
        current = high_resolution_clock::now();
        elapsed = duration_cast<duration<float, milli>>(current - previous).count();
        previous = current;

        mTickableApp->Input(elapsed);
        mTickableApp->Update(elapsed);
        mTickableApp->Display(elapsed);
    }
    spdlog::info("Brute force loop policy is ended");
}

inline long long GetTimeInMSec() {
    auto duration = high_resolution_clock::now().time_since_epoch();
    return duration_cast<milliseconds>(duration).count();
}

void GameTicker::FixFpsLoop() {
    spdlog::info("Fix fps loop policy is selected and started!");

    auto nextTickTime = GetTimeInMSec();
    long long sleepTime{0};

    auto previous(high_resolution_clock::now());
    time_point<high_resolution_clock> current;
    double elapsed{0};

    while (true == mIsTickerActive.load()) {
        mTickableApp->Input(elapsed);
        mTickableApp->Update(cPerTickSkipTimeInMsDbl);
        mTickableApp->Display(cPerTickSkipTimeInMsDbl);

        nextTickTime += cPerTickSkipTimeInMs;
        sleepTime = nextTickTime - GetTimeInMSec();

        if (sleepTime > 0) {
            std::this_thread::sleep_for(milliseconds(sleepTime));
        }

        current = high_resolution_clock::now();
        elapsed = duration_cast<duration<double, milli>>(current - previous).count();
        previous = current;
    }
    spdlog::info("Fix fps loop policy is ended!");
}

void GameTicker::VariableFpsLoop() {
    spdlog::info("Variable fps loop policy is selected and started!");

    auto previous(high_resolution_clock::now());
    time_point<high_resolution_clock> current;
    double elapsed{0};

    while (true == mIsTickerActive.load()) {
        current = high_resolution_clock::now();
        elapsed = duration_cast<duration<double, milli>>(current - previous).count();
        previous = current;

        mTickableApp->Input(elapsed);
        mTickableApp->Update(elapsed);
        mTickableApp->Display(elapsed);
    }
    spdlog::info("Variable fps loop policy is ended!");
}

void GameTicker::FixGameSpeedVariableFpsLoop() {
    spdlog::info("Fix game speed variable fps loop policy is selected and started!");

    int loops;
    double interpolation{ 0.0 };
    auto nextTickTime = GetTimeInMSec();
    auto previous(high_resolution_clock::now());
    time_point<high_resolution_clock> current;
    double elapsed{0.0};

    while (true == mIsTickerActive.load()) {
        loops = 0;
        mTickableApp->Input(elapsed);

        while (GetTimeInMSec() > nextTickTime
            &&
            loops < cMaxFrameskip) {
            mTickableApp->Update(cPerTickSkipTimeInMs);
            nextTickTime += cPerTickSkipTimeInMs;
            loops++;
        }

        mTickableApp->Display(interpolation);

        current = high_resolution_clock::now();
        elapsed = duration_cast<duration<double, milli>>(current - previous).count();
        previous = current;
    }
    spdlog::info("Fix game speed variable fps loop policy is ended!");
}

void GameTicker::ConstGameSpeedWithMaxFpsLoop() {
    spdlog::info("Const game speed with max fps loop policy is selected and started!");

    int loops;
    double interpolation{ 0.0 };
    auto nextTickTime = GetTimeInMSec();
    auto previous(high_resolution_clock::now());
    time_point<high_resolution_clock> current;
    double elapsed {0};

    while (true == mIsTickerActive.load()) {
        loops = 0;
        mTickableApp->Input(elapsed);

        while (GetTimeInMSec() > nextTickTime
            &&
            loops < cMaxFrameskip) {
            mTickableApp->Update(cPerTickSkipTimeInMs);
            nextTickTime += cPerTickSkipTimeInMs;
            loops++;
        }

        interpolation = (GetTimeInMSec() + cPerTickSkipTimeInMs - nextTickTime) / cPerTickSkipTimeInMsDbl;
        mTickableApp->Display(interpolation);

        current = high_resolution_clock::now();
        elapsed = duration_cast<duration<double, milli>>(current - previous).count();
        previous = current;
    }

    spdlog::info("Brute force loop policy is ended!");
}
