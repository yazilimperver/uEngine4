/*!
 * @file	Statistics.h.
 * @date	31.08.2021
 * @author	Yazilimperver
 * @brief	Detaylar için: https://github.com/cameron314/microbench/blob/master/microbench.h
 * @remark	Copyright (c) 2021, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <cstdint>
#include <cassert>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>
#include <string_view>

/**
 * @class Statistics
 * @brief Temel istatistiksel verileri tutmak için kullanýlabilecek sýnýftýr.
 */
class Statistics {
public:
	Statistics(double* results, std::size_t count);

	inline double min() const { return mMin; }
	inline double max() const { return mMax; }
	inline double range() const { return mMax - mMin; }
	inline double avg() const { return mAvg; }
	inline double variance() const { return mVariance; }
	inline double stddev() const { return std::sqrt(mVariance); }
	inline double median() const { return mQ[1]; }
	inline double q1() const { return mQ[0]; }
	inline double q2() const { return mQ[1]; }
	inline double q3() const { return mQ[2]; }
	inline double q(std::size_t which) const { assert(which < 4 && which > 0); return mQ[which - 1]; }

	void PrintResults();
private:
	double mMin{0};
	double mMax{ 0 };
	double mQ[3]{ 0 };
	double mAvg{ 0 };
	double mVariance{ 0 };
};

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
