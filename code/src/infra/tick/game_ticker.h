/**
 * @file game_ticker.h.
 * @date 27.03.2022
 * @author Yazilimperver
 * @brief  http://www.yazilimperver.com/index.php/2018/10/24/oyun-donguleri-ornek-kodlar/ ve 
 * 		   https://www.yazilimperver.com/index.php/2017/12/09/oyun-donguleri/ yazilarimda bahsettigim farkli loop tekniklerini iceren ticker
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef GAMETICKER_H
#define GAMETICKER_H

#include <atomic>

#include "graphical_tickable.h"

class GameTicker {
public:
	enum class LoopPolicy {
		BruteForce, // yontem 1
		FixFps,
		VariableFps,
		ConstGameSpeedWithMaxFps,
		FixGameSpeedVariableFps // yontem 5
	};

	void Execute(LoopPolicy loopPolicy);
	void AssignTickableApp(GraphicalTickable* app);
	void StopTicker();
protected:
	
	void BruteForceLoop();
	void FixFpsLoop();
	void VariableFpsLoop();
	void ConstGameSpeedWithMaxFpsLoop();
	void FixGameSpeedVariableFpsLoop();

	/** @brief Secilen dongu yaklasimi */
	LoopPolicy mLoopPolicy{ LoopPolicy::BruteForce };

	/* @brief Tetikleme ne zaman kadar devam edecek */
	std::atomic<bool> mIsTickerActive{ true };

	/* @brief Tetiklenecek olan uygulama */
	GraphicalTickable* mTickableApp{ nullptr };
};

#endif // !GAMETICKER_H

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
