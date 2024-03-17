#include "stoppable_timer.h"

StoppableTimer::~StoppableTimer() {
    Stop();
}

void StoppableTimer::Start(std::chrono::milliseconds const& duration, std::function<void(void)> const& callback) {
    // Restart gibi de cagirmak icin kullanalim
    Stop();
    mShouldStop = false;

    mThread = std::thread([=, this]() {
        auto lock = std::unique_lock<std::mutex>(mMutex);
        mCV.wait_for(lock, duration, [this]() { return mShouldStop.load(); });

        if (!mShouldStop)
            callback();
        });
}

void StoppableTimer::Stop() {
    mShouldStop = true;
    mCV.notify_one();

    if (mThread.joinable()) {
        mThread.join();
    }
}
