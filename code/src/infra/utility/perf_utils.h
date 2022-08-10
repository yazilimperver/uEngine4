/*!
 * @file	perf_utils.h.
 * @date	31.08.2021
 * @author	Yazilimperver
 * @brief    Performans ile ilgili islevler icin kullanilabilecek olan bir takim yardimci araclar
 * @remark	Copyright (c) 2021, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef PERFUTILS
#define PERFUTILS

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <functional>

#include "statistics.h"

namespace Tools {
    class PerfUtils {
    public:
        /*!
         * @brief	Multithreaded olcum islemleri icin kullanilabilecek yardimci fonksiyondur
         *
         * @returns	Olcumler dizi olarak donulur. Her eleman ilgili iterasyon ve verilen test kosum adeti icin harcanan zamani sn cinsinden doner
         */
        static std::vector<double> MultithreadedBenchEntry(std::function<void(int)> threadFunc, int threadCount, int testRunCount, int iterationCount = 1);

        /*!
         * @brief	Verilen fonksiyon tek bir thread icerisinde, verilen adet kadar kosturmak icin kullanilir
         *
         * @returns	Olcumler dizi olarak donulur. Her eleman ilgili iterasyon ve verilen test kosum adeti icin harcanan zamani sn cinsinden doner
         */
        static std::vector<double> SinglethreadedBenchEntry(std::function<void()> threadFunc, int testRunCount, int iterationCount);

        /*!
         * @brief	Tek bir thread icerisinde yaptigi olcumler icin istatistikleri tutmak icin kullanilir
         *
         * @returns	Ilgili istatistikler donulur
         */
        static Statistics BenchWithStats(std::function<void()> func, std::uint64_t iterations = 1, std::uint32_t testRuns = 100);

        /*!
         * @brief	Ýlgili ölçüm sonuçlarýný bastýrmak ve görüntülemek için kullanýlacak fonksiyonlar
         */
        static void PrintResults(const std::vector<double>& results, int testRunCount, int iterationCount);
        static void PrintResultsToFile(const char* fileName, const char* testName, const std::vector<double>& results, int testRunCount, int iterationCount, bool doAppend = false);
        static void PrintResultsToFile(const char* fileName, const char* testName, const Statistics& results, int testRunCount, int iterationCount, bool doAppend = false);
    };
}

#endif // !PERFUTILS

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
