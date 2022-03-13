/*!
 * @file	sleep_util.h.
 * @date	8.03.2022
 * @author	Yazilimperver
 * @brief
 * @remark	Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <cstdint>

class SleepUtil {
public:
	static void USleep(int64_t sleepInUSec);
	static void PreciseSleep(double seconds);
};
