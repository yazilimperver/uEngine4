#include "fps_timer.h"
#include "spdlog/spdlog.h"

#include "sleep_util.h"

using namespace std::chrono;

FPSTimer::FPSTimer(double theTargetFps, uint32_t reportInterval)
	: mFrameDuration{ 1 }
	, mIsReportingEnabled{ false } {

	SetFPSParameters(theTargetFps, reportInterval);
}

void FPSTimer::SetFPSParameters(double theTargetFps, uint32_t reportInterval) {
	mFrameStartTime = high_resolution_clock::now();
	mFrameEndTime = mFrameStartTime + milliseconds(1);

	this->SetTargetFps(theTargetFps);
	this->SetReportIntervalInSec(reportInterval);
}

milliseconds FPSTimer::FPSCheck() {
	mFrameEndTime = high_resolution_clock::now();

	nanoseconds durat = mFrameEndTime - mFrameStartTime;
	mFrameDuration = duration_cast<milliseconds>(durat);

	if (true == mIsReportingEnabled) {
		if ((mFrameEndTime - mLastReportTime) > mReportInterval) {
			double reportDurationInSec = duration_cast<milliseconds>(mFrameEndTime - mLastReportTime).count() * 0.001;
			mLastReportTime = mFrameEndTime;
			// +1 son periyodu da ekleyelim
			mCurrentFps = round(static_cast<double>(mFrameCount) / mReportIntervalInSeconds) + 1;
			mFrameCount = 1;

			spdlog::info("The FPS: {}. The average frame time: {:.03f} ms!", mCurrentFps, static_cast<double>(reportDurationInSec) / mFrameCount);
		}
		else  {
			++mFrameCount;
		}

	}
	mSleepDuration = mTargetFrameDurationInMsec - mFrameDuration;

	if (mSleepDuration.count() > 0.0)	{
		SleepUtil::PreciseSleep(mTargetFrameDurationInSec);
	}
	mFrameStartTime = high_resolution_clock::now();
	return (mFrameDuration + duration_cast<milliseconds>(mFrameStartTime - mFrameEndTime));
}

double FPSTimer::GetCurrentFps() const {
	return mCurrentFps;
}

double FPSTimer::GetTargetFps() const {
	return mTargetFps;
}

void FPSTimer::SetTargetFps(double theFpsLimit) {
	if (theFpsLimit < cMIN_TARGET_FPS)	{
		theFpsLimit = cMIN_TARGET_FPS;
		spdlog::info("Limiting FPS rate to legal minimum of {} frames per second.", cMIN_TARGET_FPS);
	}
	if (theFpsLimit >= cMAX_TARGET_FPS)	{
		theFpsLimit = cMAX_TARGET_FPS;
		spdlog::info("Limiting FPS rate to legal maximum of {} frames per second.", cMAX_TARGET_FPS);
	}

	mTargetFps = theFpsLimit;

	mTargetFrameDurationInSec = 1.0 / mTargetFps;
	duration<double> targetDurationInSeconds{ mTargetFrameDurationInSec };

	mTargetFrameDurationInMsec = duration_cast<milliseconds>(targetDurationInSeconds);
}

void FPSTimer::EnableReporting() {
	mIsReportingEnabled = true;
}

void FPSTimer::DisableReporting() {
	mIsReportingEnabled = false;
}

double FPSTimer::GetReportIntervalInSec() const {
	return mReportIntervalInSeconds;
}

void FPSTimer::SetReportIntervalInSec(uint32_t val) {
	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (val < 100) {
		val = 100;
	}
	if (val > 10000) {
		val = 10000;
	}

	mReportIntervalInSeconds = static_cast<double>(val) / 1000.0F;

	mReportInterval = duration_cast<nanoseconds> (milliseconds(val));
}