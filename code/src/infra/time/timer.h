/**
 * @file timer.h.
 * @date 5.03.2023
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2023, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <atomic>

#include "sleep_util.h"

class Timer {
public:
    void SetTimeout(auto function, int delayInMsec);
    void SetInterval(auto function, int intervalInMsec);
    void Stop();

protected:
    std::atomic<bool> mActive{ true };
};

void Timer::SetTimeout(auto function, int delayInMsec) {
    mActive = true;
    std::thread t([=]() {
        if (!mActive.load())
            return;

        //std::this_thread::sleep_for(std::chrono::milliseconds(delayInMsec));
        SleepUtil::PreciseSleep(delayInMsec / 1000.0);

        if (!mActive.load())
            return;

        function();
        });

    t.detach();
}

void Timer::SetInterval(auto function, int intervalInMsec) {
    mActive = true;
    std::thread t([=]() {
        while (mActive.load()) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(intervalInMsec));
            SleepUtil::PreciseSleep(intervalInMsec / 1000.0);

            if (!mActive.load())
                return;

            function();
        }
        });

    t.detach();
}

void Timer::Stop() {
    mActive = false;
}
#endif // !TIMER_H


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
