/**
 * @file threaded_timer.h.
 * @date 7.03.2023
 * @author Yazilimperver
 * @brief Yuksek hassasiyete sahip, threaded timer. 
 * @remark Copyright (c) 2023, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#include "concurrency/thread_base.h"

#ifndef THREADED_TIMER_H
#define THREADED_TIMER_H

class ThreadedTimer {
public:
    virtual ~ThreadedTimer();
    void OneShot(auto function, int32_t delayInMsec);
    void Periodic(auto function, int32_t intervalInMsec);
    void Stop();
    void WaitForCompletion();

protected:
    std::atomic<bool> mActive{ true };
    std::unique_ptr<std::thread> mThread{ nullptr };
};

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
    mThread = std::make_unique<std::thread>([=]() {
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
    mThread = std::make_unique<std::thread>([=]() {
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

#endif // !THREADED_TIMER_H
