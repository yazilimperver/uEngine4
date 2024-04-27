#include "sdl_app_ticker.h"

#include <chrono>

#include "spdlog/spdlog.h"

using namespace std::chrono;

inline long long GetTimeInMSec() {
	auto duration = high_resolution_clock::now().time_since_epoch();
	return duration_cast<milliseconds>(duration).count();
}

void SdlAppTicker::Execute(int32_t targetFps) {
	if (nullptr == mTickableApp) {
		spdlog::error("No tickable app is registered!");
		return;
	}
	if (mIsTickerActive.is_lock_free()) {
		spdlog::info("Ticker control flag is not atomic, check it!");
	}

	spdlog::info("Tick time interval {:0.3f} msec", 1.0 / targetFps * 1000.0);

	mTickData.TickPerSeconds = targetFps;
	mTickData.SkipTicksInMsec = 1000 / mTickData.TickPerSeconds;
	mTickData.MaxFrameCountToSkip = 15;

	high_resolution_clock::time_point currentTime;
	high_resolution_clock::time_point previousTime = high_resolution_clock::now();
	double elapsedInMsec{ 0.0 };
	auto nextGameTick = GetTimeInMSec();

	double interpolation{ 0 };
	int32_t loopCount{ 0 };
	while (true == mIsTickerActive.load()) {
		mTickableApp->Input(elapsedInMsec);

		loopCount = 0;
		while ((GetTimeInMSec() > nextGameTick)
			&&
			(loopCount < mTickData.MaxFrameCountToSkip)) {
			mTickableApp->Update(mTickData.SkipTicksInMsec);

			nextGameTick += mTickData.SkipTicksInMsec;
			loopCount++;
		}

		interpolation = static_cast<double>(GetTimeInMSec() + mTickData.SkipTicksInMsec - nextGameTick) / static_cast<double>(mTickData.SkipTicksInMsec);

		mTickableApp->Display(interpolation);

		// dongu hesaplamalari
		currentTime = high_resolution_clock::now();
		elapsedInMsec = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count()) * 0.000001;
		previousTime = currentTime;
	}
}

void SdlAppTicker::AssignTickableApp(GraphicalTickable* app) {
	mTickableApp = app;
}

const TickData& SdlAppTicker::GetTickData() const {
	return mTickData;
}

void SdlAppTicker::StopTicker() {
	mIsTickerActive.store(false);
}
