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

    std::chrono::milliseconds FPSCheck();

    double GetCurrentFps() const;
    double GetTargetFps() const;
    void SetTargetFps(double theFpsLimit);    
    void EnableReporting();
    void DisableReporting();
    double GetReportIntervalInSec() const;    
    void SetReportIntervalInSec(uint32_t val);
protected:

    // Minimum allowed fps
    const double cMIN_TARGET_FPS = 10.0;

    // If you set this above the refresh of your monitor and enable VSync it'll break! Be aware!
    const double cMAX_TARGET_FPS = 120.0;

    // Frame start time
    std::chrono::high_resolution_clock::time_point mFrameStartTime;

    // Frame end time
    std::chrono::high_resolution_clock::time_point mFrameEndTime;

    // How many milliseconds between the last frame and this frame
    std::chrono::milliseconds mFrameDuration;

    // The desired FPS to run at (i.e. maxFPS)
    double mTargetFps;

    // The current FPS value 
    double mCurrentFps;

    // How many frames have been drawn s
    int32_t mFrameCount;

    // How many milliseconds each frame should take to hit a target FPS value (i.e. 60fps = 1.0 / 60 = 0.016ms)
    double mTargetFrameDurationInSec{ 0 };
    std::chrono::milliseconds mTargetFrameDurationInMsec{ 0 };

    // How long to sleep if we're exceeding the target frame rate duration
    std::chrono::milliseconds mSleepDuration;

    // The timestamp of when we last reported
    std::chrono::high_resolution_clock::time_point mLastReportTime;

    // Is reporting enabled
    bool mIsReportingEnabled;

    // How often to update the FPS value
    double mReportIntervalInSeconds;
    std::chrono::nanoseconds mReportInterval;
};

#endif // FPSTIMER_H__