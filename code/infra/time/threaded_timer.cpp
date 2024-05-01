#include "threaded_timer.h"
#include "sleep_util.h"

ThreadedTimer::~ThreadedTimer() {
    mActive.store(false);

    if (nullptr != mThread) {
        if (mThread->joinable()) {
            mThread->join();
        }
    }
}

void ThreadedTimer::OneShot(auto function, int32_t delayInMsec) {
    mActive = true;
    mThread = std::make_unique<std::thread>([=, this]() {
        if (!mActive.load())
            return;
        SleepUtil::PreciseSleep(delayInMsec / 1000.0);

        if (!mActive.load())
            return;

        function();
        });
}

void ThreadedTimer::Periodic(auto function, int32_t intervalInMsec) {
    mActive = true;
    mThread = std::make_unique<std::thread>([=, this]() {
        while (mActive.load()) {
            SleepUtil::PreciseSleep(intervalInMsec / 1000.0);

            if (!mActive.load())
                return;

            function();
        }
        });
}

void ThreadedTimer::Stop() {
    mActive = false;
}

void ThreadedTimer::WaitForCompletion() {
    if (nullptr != mThread) {
        if (mThread->joinable()) {
            mThread->join();
        }
    }
}
