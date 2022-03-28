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
