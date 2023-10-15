/**
 * @file fps_timer.h.
 * @date 21.03.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef FPSTIMER_H__
#define FPSTIMER_H__

#include <cstdint>
#include <chrono>
class FPSTimer {
public:
    FPSTimer(double theTargetFps = 60, uint32_t reportInterval = 1000);

    void SetFPSParameters(double theTargetFps, uint32_t reportInterval);

    /**
     * @brief   Temel FPS sinirlamasinin kotarilmasindan sorumlu olan siniftir
     * @returns Bir onceki frame zamani ve tick zaman toplami
     */

    std::chrono::milliseconds FPSCheck();

    double GetCurrentFps() const;
    double GetTargetFps() const;
    void SetTargetFps(double theFpsLimit);    
    void EnableReporting();
    void DisableReporting();
    double GetReportIntervalInSec() const;    
    void SetReportIntervalInSec(uint32_t val);
protected:

    /** @brief Izin verilen minimum FPS */
    const double cMIN_TARGET_FPS = 10.0;

    /** @brief Izin verilen maksimum FPS, bu degerleri belirlerken monitorun VSYNC durumuna dikkat edilmeli! */
    const double cMAX_TARGET_FPS = 120.0;

    /** @brief Frame baslangic zamani */
    std::chrono::high_resolution_clock::time_point mFrameStartTime;

    /** @brief Frame bitis zamani */
    std::chrono::high_resolution_clock::time_point mFrameEndTime;

    /** @brief En son gecen frame zamaninin milisaniye cinsinden karsiligi */
    std::chrono::milliseconds mFrameDuration;

    /** @brief Hedeflenen FPS degeri */
    double mTargetFps;

    /** @brief En son hesaplanan FPS degeri */
    double mCurrentFps;

    /** @brief Hedeflenen FPS icin, ilgili frame'in milisaniye cinsinden ne kadar surecegini tutar */
    double mTargetFrameDurationInSec{ 0 };
    std::chrono::milliseconds mTargetFrameDurationInMsec{ 0 };

    /** @brief En son FPS raporlama zamani */
    std::chrono::high_resolution_clock::time_point mLastReportTime;

    /** @brief Raporlama aktif mi */
    bool mIsReportingEnabled;

    /** @brief FPS degeri ne kadar zamanda bir raporlanacak */
    double mReportIntervalInSeconds;
    std::chrono::nanoseconds mReportInterval;
};

#endif // FPSTIMER_H__

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

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