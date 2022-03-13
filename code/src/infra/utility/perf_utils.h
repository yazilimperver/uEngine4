/*!
 * @file	perf_utils.h.
 * @date	31.08.2021
 * @author	Yazilimperver
 * @brief
 * @remark	Copyright (c) 2021, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <atomic>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <functional>

#include "statistics.h"

namespace Tools {

    /*!
     * @class	PerfUtils
     *
     * @brief	Performans ile ilgili islevler icin kullanilabilecek olan yardimc araclar
     */
    class PerfUtils {
    public:
        /*!
         * @brief	Multithreaded olcum islemleri icin kullanilabilecek yardimci fonksiyondur
         *
         * @returns	Olcumler dizi olarak donulur. Her eleman ilgili iterasyon ve verilen test kosum adeti icin harcanan zamani sn cinsinden doner
         */
        static std::vector<double> MultithreadedBenchEntry(std::function<void(int)> threadFunc, int threadCount, int testRunCount, int iterationCount = 1);

        /*!
         * @brief	Singlethreaded bench entry
         *
         * @returns	Olcumler dizi olarak donulur. Her eleman ilgili iterasyon ve verilen test kosum adeti icin harcanan zamani sn cinsinden doner
         */
        static std::vector<double> SinglethreadedBenchEntry(std::function<void()> threadFunc, int testRunCount, int iterationCount);

        /*!
         * @brief	Bench with statistics
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