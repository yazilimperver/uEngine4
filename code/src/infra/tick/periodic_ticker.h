#ifndef PERIODICTICKER_H
#define PERIODICTICKER_H

#include <atomic>

#include "tickable.h"

class PeriodicTicker {
public:
	void Execute(double periodInMsec);
	void SetInterval(double periodInMsec);
	void AssignTickableApp(Tickable* app);
	void StopTicker();
protected:

	/* @brief Periodiklik icin kullanilacak olan sure */
	double mPeriodicityInSec{0.01};

	/* @brief Tetikleme ne zaman kadar devam edecek */
	std::atomic<bool> mIsTickerActive{ true };

	/* @brief Tetiklenecek olan uygulama */
	Tickable* mTickableApp{ nullptr };
};

#endif // !PERIODICTICKER_H

