/**
 * @file std_active_object.h
 * @author yazilimperver (yazilimperver@gmail.com)
 * @brief std::queue kullanan basit bir aktif nesne ornegimiz. Burada ozellikle boost kullanilmadi
 * @date 2023-06-05
 * @todo Periyodik/TekAtim sayac API'lerinin consolide edilmesi
 *       Hassas sayac (spin lock vs) kullanimi
 */

#include <iostream>
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <condition_variable>

#ifndef INC_STD_ACTIVE_OBJECT_H
#define INC_STD_ACTIVE_OBJECT_H

/**
* @brief Boost kullanmayan aktif nesne sinifimiz
*/
class StdActiveObject {
public:
    /* @brief Yeni bir aktif nesne olusturup, ilgili olay dongusunu bagimsiz bir threadte baslatir.*/
    StdActiveObject();

    /* @brief Aktif nesneyi sonlandiriyoruz. Tasi taragi topluyoruz */
    virtual ~StdActiveObject();

    /* @brief Aktif nesneye arguman alan bir is gecirmek icin kullanabilecegimiz API */
    template<typename Function, typename... Args>
    void PostEvent(Function&& function, Args&&... args);

    /* @brief Tek seferlik zaman olayi */
    template<typename Function, typename Duration, typename... Args>
    uint64_t PostOneTimeTimerEvent(Function eventHandler, const Duration& duration, Args&&... args);

    /* @brief Periyodik sayaci baslatmak icin kullanilacak API */
    template<typename Function, typename Duration, typename... Args>
    uint64_t PostPeriodicTimerEvent(Function eventHandler, const Duration& duration, Args&&... args);

    /* @brief Periyodik sayaci durdurmak icin kullanilabilecek API */
    void StopPeriodicTimer(uint64_t index);

    /* @brief Aktif nesneyi durdurmak icin kullanilabilecek API */
    void Stop();

    /* @brief Aktif nesne icin kullanilacak olan tipler */
    using TaskContainer = std::queue<std::function<void()>>;
    using TimerThreadContainer = std::unordered_map<uint64_t, std::thread>;
    using StopFlagsContainer = std::unordered_map<uint64_t, std::shared_ptr<std::atomic<bool>>>;

    /* @brief Aktif nesne icin kullanilabilecek kontrol API'leri */
    bool IsActive() const;    
    const TaskContainer& ObtainTaskQueue() const;
    const TimerThreadContainer& ObtainPeriodicTimers() const;
    const StopFlagsContainer& ObtainPeriodicTimerStopFlags() const;
    const TimerThreadContainer& ObtainOneShotTimers() const;
protected:
    /* @brief Aktif nesneye iliskin olaylari eritecek API */
    void EventLoop();

    uint64_t unUniqueID{ 0 };
    std::mutex mMutex;
    std::condition_variable mCV;
    std::atomic<bool> mShouldStop{ false };
    std::mutex mTimerMutex;
    std::thread mThread;

    TaskContainer mTaskQueue;
    TimerThreadContainer mPeriodicTimerThreads;
    TimerThreadContainer mOneShotTimerThreads;
    StopFlagsContainer mPeriodicTimerStopFlags;
};

template<typename Function, typename ...Args>
inline void StdActiveObject::PostEvent(Function&& eventHandler, Args && ...args) {
    {
#if __cplusplus >= 202002L
        auto eventFunc = [eventHandler = std::move(eventHandler), &args...]() mutable {
            std::invoke(eventHandler, args...);
    };
#else 
        auto eventFunc = [eventHandler = std::move(eventHandler), argsTuple = std::tie(args...)]() mutable {
            std::apply(eventHandler, argsTuple);
        };
#endif
        std::lock_guard<std::mutex> lock(mMutex);
        mTaskQueue.emplace(eventFunc);
    }
    mCV.notify_one();
}

template<typename Function, typename Duration, typename ...Args>
inline uint64_t StdActiveObject::PostOneTimeTimerEvent(Function eventHandler, const Duration& duration, Args && ...args) {
    uint64_t unTimerId = unUniqueID;
    
#if __cplusplus >= 202002L
    auto timerEventFunc = [eventHandler = std::move(eventHandler), &args...]() mutable {
        std::invoke(eventHandler, args...);
    };
#else        
    // C++ 17 icin ise std::tie ile bir takla gerekiyor
    auto timerEventFunc = [this, unTimerId, eventHandler = std::move(eventHandler), argsTuple = std::tie(args...)]() mutable {
        std::apply(eventHandler, argsTuple);
        mOneShotTimerThreads[unTimerId].join();
        mOneShotTimerThreads.erase(unTimerId);
    };
#endif
    std::thread timerThread([this, timerEventFunc = std::move(timerEventFunc), duration]() {
        std::this_thread::sleep_for(duration);
        PostEvent(timerEventFunc);
        });

    std::lock_guard<std::mutex> lock(mTimerMutex);
    mOneShotTimerThreads.emplace(std::make_pair(unTimerId, std::move(timerThread)));
    unUniqueID++;

    return (unUniqueID - 1);
}

template<typename Function, typename Duration, typename ...Args>
inline uint64_t StdActiveObject::PostPeriodicTimerEvent(Function eventHandler, const Duration& duration, Args && ...args) {
    // C++ 20 de asagidaki gibi de olabiliyor
#if __cplusplus >= 202002L
    auto timerEventFunc = [eventHandler = std::move(eventHandler), &args...]() mutable {
        std::invoke(eventHandler, args...);
    };
#else        
    // C++ 17 icin ise std::tie ile bir takla gerekiyor
    auto timerEventFunc = [eventHandler = std::move(eventHandler), argsTuple = std::tie(args...)]() mutable {
        std::apply(eventHandler, argsTuple);
    };
#endif        

    // Periyodik olarak cagirmaya yonelik kod parcasi
    uint64_t unTimerId = unUniqueID;
    std::shared_ptr<std::atomic<bool>> stopFlag = std::make_shared<std::atomic<bool>>(false);
    std::thread timerThread([this, unTimerId, timerEventFunc = std::move(timerEventFunc), duration, stopFlag]() {
        while (!(*stopFlag)) {
            PostEvent(timerEventFunc);

            // TODO: Daha hassas bekleme ekleyelim
            std::this_thread::sleep_for(duration);
        }
        
        // Burada artik ilgili sayac threadini ve stop flagini silmek icin bilgilendirme yapalim
        PostEvent([this, unTimerId]() {
                if (mPeriodicTimerThreads[unTimerId].joinable()) {
                    mPeriodicTimerThreads[unTimerId].join();
                }

                std::lock_guard<std::mutex> lock(mTimerMutex);
                mPeriodicTimerThreads.erase(unTimerId);
                mPeriodicTimerStopFlags.erase(unTimerId);
            });
        });

    std::lock_guard<std::mutex> lock(mTimerMutex);

    // Thread kontrolu icin bunu tasiyalim
    mPeriodicTimerThreads.emplace(std::make_pair(unTimerId, std::move(timerThread)));

    // Ilgili sayaci durdurmak icin tasiyalim
    mPeriodicTimerStopFlags.emplace(std::make_pair(unTimerId, stopFlag));
    unUniqueID++;

    return (unUniqueID - 1);
}

#endif	// INC_STD_ACTIVE_OBJECT_H

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