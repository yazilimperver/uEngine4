/**
 * @file fps_ticker.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief  FPS sinirlama kabiliyetini kullanan ticker sinifidir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef FPSTICKER_H
#define FPSTICKER_H

#include "time/fps_timer.h"
#include "tickable.h"
#include <atomic>

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
