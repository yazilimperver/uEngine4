#ifndef FPSTICKER_H
#define FPSTICKER_H

#include "time/fps_timer.h"
#include "tickable.h"

class FpsTicker {
public:
	void Execute();
	void SetFPSParameters(double theTargetFps, uint32_t reportInterval);
	void EnableReporting();
	void DisableReporting();
	void AssignTickableApp(Tickable* app);
	void StopTicker();
protected:
	
	/* @brief Tick zamanlama kontrolu icin kullanacagimiz sinif */
	FPSTimer mFpsTimer{ 60, 1000 };

	/* @brief Tetikleme ne zaman kadar devam edecek */
	std::atomic<bool> mIsTickerActive{ true };

	/* @brief Tetiklenecek olan uygulama */
	Tickable* mTickableApp{nullptr};
};

#endif // !FPSTICKER_H

