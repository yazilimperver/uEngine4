/**
 * @file sdl_app_ticker.h.
 * @date 27.03.2022
 * @author Yazilimperver
 * @brief  Periyodik olarak saglanan sinifi tetiklemek icin kullanilacaktir
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

