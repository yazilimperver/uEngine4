#include "std_active_object.h"

StdActiveObject::StdActiveObject()
    : mThread([this] { EventLoop(); }) {
}

StdActiveObject::~StdActiveObject() {
    Stop();
}

void StdActiveObject::StopPeriodicTimer(uint64_t index) {
    if (auto itr = mPeriodicTimerThreads.find(index); itr != mPeriodicTimerThreads.end()) {
        *mPeriodicTimerStopFlags[index] = true;
    }
}

void StdActiveObject::Stop() {
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mShouldStop = true;
    }

    mCV.notify_all();

    for (auto& stopFlag : mPeriodicTimerStopFlags) {
        *stopFlag.second = true;
    }

    for (auto& timerThread : mPeriodicTimerThreads) {
        if (timerThread.second.joinable()) {
            timerThread.second.join();
        }
    }

    mPeriodicTimerThreads.clear();
    mPeriodicTimerStopFlags.clear();

    for (auto& timerThread : mOneShotTimerThreads) {
        if (timerThread.second.joinable()) {
            timerThread.second.join();
        }
    }

    mOneShotTimerThreads.clear();

    if (mThread.joinable()) {
        mThread.join();
    }
}

const std::queue<std::function<void()>>& StdActiveObject::ObtainTaskQueue() const {
    return mTaskQueue;
}

const StdActiveObject::TimerThreadContainer& StdActiveObject::ObtainPeriodicTimers() const {
    return mPeriodicTimerThreads;
}

const StdActiveObject::StopFlagsContainer& StdActiveObject::ObtainPeriodicTimerStopFlags() const {
    return mPeriodicTimerStopFlags;
}

const StdActiveObject::TimerThreadContainer& StdActiveObject::ObtainOneShotTimers() const {
    return mOneShotTimerThreads;
}

bool StdActiveObject::IsActive() const {
    return (false == mShouldStop);
}

void StdActiveObject::EventLoop() {
    while (!mShouldStop) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mCV.wait(lock, [this] { return mShouldStop || !mTaskQueue.empty(); });
            if (mShouldStop && mTaskQueue.empty()) {
                break;
            }
            task = std::move(mTaskQueue.front());
            mTaskQueue.pop();
        }

        task();
    }
}
