#include "Statistics.h"
#include <fstream>
#include "fmt/core.h"

Statistics::Statistics(double* results, std::size_t count) {
	if (nullptr != results) {
		std::sort(results, results + count);

		mMin = results[0];
		mMax = results[count - 1];

		if (count == 1) {
			mQ[0] = mQ[1] = mQ[2] = results[0];
			mAvg = results[0];
			mVariance = 0;
			return;
		}

		// Kahan summation to reduce error (see http://en.wikipedia.org/wiki/Kahan_summation_algorithm)
		double sum = 0;
		double c = 0;	// Error last time around
		for (std::size_t i = 0; i != count; ++i) {
			auto y = results[i] - c;
			auto t = sum + y;
			c = (t - sum) - y;
			sum = t;
		}
		mAvg = sum / count;

		// Calculate unbiased (corrected) sample variance
		sum = 0, c = 0;
		for (std::size_t i = 0; i != count; ++i) {
			auto y = (results[i] - mAvg) * (results[i] - mAvg) - c;
			auto t = sum + y;
			c = (t - sum) - y;
			sum = t;
		}
		mVariance = sum / (count - 1);

		// See Method 3 here: http://en.wikipedia.org/wiki/Quartile
		mQ[1] = (count & 1) == 0 ? (results[count / 2 - 1] + results[count / 2]) * 0.5 : results[count / 2];
		if ((count & 1) == 0) {
			mQ[0] = (count & 3) == 0 ? (results[count / 4 - 1] + results[count / 4]) * 0.5 : results[count / 4];
			mQ[2] = (count & 3) == 0 ? (results[count / 2 + count / 4 - 1] + results[count / 2 + count / 4]) * 0.5 : results[count / 2 + count / 4];
		}
		else if ((count & 3) == 1) {
			mQ[0] = results[count / 4 - 1] * 0.25 + results[count / 4] * 0.75;
			mQ[2] = results[count / 4 * 3] * 0.75 + results[count / 4 * 3 + 1] * 0.25;
		}
		else {		// (count & 3) == 3
			mQ[0] = results[count / 4] * 0.75 + results[count / 4 + 1] * 0.25;
			mQ[2] = results[count / 4 * 3 + 1] * 0.25 + results[count / 4 * 3 + 2] * 0.75;
		}
	}
}

void Statistics::PrintResults() {
	printf("CAS statistics: avg: %.3fms, min: %.3fms, max: %.3fms, stddev: %.3fms, Q1: %.3fms, median: %.3fms, Q3: %.3fms\n",
		avg() * 1000,
		min() * 1000,
		max() * 1000,
		stddev() * 1000,
		q1() * 1000,
		median() * 1000,
		q3() * 1000);
}