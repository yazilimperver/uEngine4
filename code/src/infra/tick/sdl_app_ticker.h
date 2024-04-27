/**
 * @file sdl_app_ticker.h.
 * @date 27.03.2022
 * @author Yazilimperver
 * @brief  Periyodik olarak saglanan, grafiksel uygulamalara iliskin sinifi tetiklemek icin kullanilacaktir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef SDLAPPTICKER_H
#define SDLAPPTICKER_H

#include <atomic>

#include "graphical_tickable.h"

#include "tick_data.h"

class SdlAppTicker {
public:
	void Execute(int32_t targetFps);
	void AssignTickableApp(GraphicalTickable* app);

	const TickData& GetTickData() const;
	void StopTicker();
protected:

	/* @brief Tetikleme ne zaman kadar devam edecek */
	std::atomic<bool> mIsTickerActive{ true };

	/* @brief Tetiklenecek olan uygulama */
	GraphicalTickable* mTickableApp{ nullptr };

	//! The tick configuration data
	TickData mTickData;
};

#endif // !SDLAPPTICKER_H

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
