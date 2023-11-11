#include "timer.h"

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