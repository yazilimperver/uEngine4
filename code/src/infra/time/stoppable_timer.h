/**
 * @file   stoppable_timer.h
 * @date   9/12/2023
 * @author Yazilimperver
 * @brief
 * @remark
 */

#ifndef INC_STOPPABLE_TIMER_H
#define INC_STOPPABLE_TIMER_H

#include <chrono>
#include <thread>
#include <functional>
#include <condition_variable>

class StoppableTimer {
public:

    StoppableTimer() {}
    ~StoppableTimer() {
        Stop();
    }

    void Start(std::chrono::milliseconds const& duration, std::function<void(void)> const& callback) {
        // Restart gibi de cagirmak icin kullanalim
        Stop();
        mShouldStop = false;

        mThread = std::thread([=]() {
            auto lock = std::unique_lock<std::mutex>(mMutex);
            mCV.wait_for(lock, duration, [this]() { return mShouldStop.load(); });

            if (!mShouldStop)
                callback();
        });
    }

    void Stop()    {
        mShouldStop = true;
        mCV.notify_one();

       if (mThread.joinable()) {
            mThread.join();
        }
    }

private:

    std::atomic<bool> mShouldStop;
    std::thread mThread;
    std::mutex mMutex;
    std::condition_variable mCV;
};

#endif	// INC_STOPPABLE_TIMER_H

/**
Copyright (c) [2023][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


