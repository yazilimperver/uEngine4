#include "perf_utils.h"
#include <fstream>
#include "fmt/core.h"

using namespace std;
using namespace std::chrono;

namespace Tools {
    /*!
    * @brief	Multithreaded olcum islemleri icin kullanilabilecek yardimci fonksiyondur
    *
    * @param 	threadCount   	Thread sayisi
    * @param 	messageCount  	Mesaj adeti.
    * @param 	iterationCount	(Opsiyonel) Iterasyon sayisi.
    */
    std::vector<double>  PerfUtils::MultithreadedBenchEntry(std::function<void(int)> threadFunc, int threadCount, int testRunCount, int iterationCount) {
        using std::chrono::high_resolution_clock;
        std::vector<double> results(iterationCount, 0);

        for (int itr = 0; itr < iterationCount; ++itr) {
            vector<thread> threads;
            auto start = high_resolution_clock::now();

            // Thread'leri baslatalim
            for (int t = 0; t < threadCount; ++t) {
                threads.push_back(std::thread(threadFunc, testRunCount));
            }

            // Threadleri bekleyelim
            for (auto& t : threads) {
                t.join();
            };

            auto delta = high_resolution_clock::now() - start;
            auto delta_d = duration_cast<duration<double>>(delta).count();

            results[itr] = delta_d;
        }

        PerfUtils::PrintResults(results, testRunCount, iterationCount);
        fmt::print("PerfUtils::MultithreadedBenchEntry completed\n");

        return results;
    }

    std::vector<double>  PerfUtils::SinglethreadedBenchEntry(std::function<void()> threadFunc, int testRunCount, int iterationCount) {

        using std::chrono::high_resolution_clock;
        std::vector<double> results(iterationCount, 0);

        for (int itr = 0; itr < iterationCount; ++itr) {
            vector<thread> threads;
            auto start = high_resolution_clock::now();

            // Thread'leri baslatalim
            for (int t = 0; t < testRunCount; ++t) {
                threadFunc();
            }

            auto delta = high_resolution_clock::now() - start;
            auto delta_d = duration_cast<duration<double>>(delta).count();

            results[itr] = delta_d;
        }

        PerfUtils::PrintResults(results, testRunCount, iterationCount);

        return results;
    }

    Statistics PerfUtils::BenchWithStats(std::function<void()> func, std::uint64_t iterations, std::uint32_t testRunCount)
    {
        assert(testRunCount >= 1);
        assert(iterations >= 1);

        std::vector<double> results(testRunCount, 0);

        for (std::uint32_t i = 0; i < testRunCount; ++i) {
            auto start = high_resolution_clock::now();

            for (std::uint64_t j = 0; j < iterations; ++j) {
                func();
            }

            results[i] = duration_cast<duration<double>>(high_resolution_clock::now() - start).count();

            results[i] /= iterations;
        }

        return Statistics(&results[0], results.size());
    }

    void PerfUtils::PrintResults(const std::vector<double>& results, int testRunCount, int iterationCount)
    {
        int i{ 0 };
        double totalTimeInSec{ 0.0 };

        for (auto time : results) {
            fmt::print("[Iteration {}] Elapsed: {:.03f} secs\t {:.03f} msec \t PerMsg: {:.03f} msec \n", i++ + 1, time, time * 1000.0, time * 1000.0 / testRunCount);
            totalTimeInSec += time;
        }

        fmt::print("\nItr. Avrg. Elapsed: {:.03f} secs\t {:.03f} msec \t PerMsg: {:.03f} msec \n", totalTimeInSec / iterationCount, totalTimeInSec / iterationCount * 1000.0, totalTimeInSec / iterationCount * 1000.0 / testRunCount);
    }

    void PerfUtils::PrintResultsToFile(const char* fileName, const char* testName, const std::vector<double>& results, int testRunCount, int iterationCount, bool doAppend)
    {
        /* Test Name:
        *  Test Run Count:
        *  Test Iteration Count:
        */
        std::ofstream file;

        if (doAppend)
            file.open(fileName, std::ios_base::app);
        else
            file.open(fileName);

        if (file.is_open()) {
            file << "#######################################################################\n"
                << "# Test Name             : " << testName << "\n"
                << "# Test Run Count        : " << testRunCount << "\n"
                << "# Test Iteration Count  : " << iterationCount << "\n";

            int i{ 0 };
            double totalTimeInSec{ 0.0 };
            for (auto time : results) {
                file << "# " << fmt::format("[Iteration {}] Elapsed : {:.03f} secs\t {:.03f} msec \t PerMsg: {:.03f} msec \n", i++ + 1, time, time * 1000.0, time * 1000.0 / testRunCount);
                totalTimeInSec += time;
            }

            file << "# " << fmt::format("Itr. Avrg. Elapsed    : {:.03f} secs\t {:.03f} msec \t PerMsg: {:.03f} msec \n", totalTimeInSec / iterationCount, totalTimeInSec / iterationCount * 1000.0, totalTimeInSec / iterationCount * 1000.0 / testRunCount);


            file << "#######################################################################\n\n";
        }

        file.close();
    }

    void PerfUtils::PrintResultsToFile(const char* fileName, const char* testName, const Statistics& results, int testRunCount, int iterationCount, bool doAppend)
    {
        /* Test Name:
        *  Test Run Count:
        *  Test Iteration Count:
        */
        std::ofstream file;

        if (doAppend)
            file.open(fileName, std::ios_base::app);
        else
            file.open(fileName);

        constexpr double secToMsec = 1000.0;

        if (file.is_open()) {
            file << "#######################################################################\n"
                << "# Test Name            : " << testName << "\n"
                << "# Test Run Count       : " << testRunCount << "\n"
                << "# Test Iteration Count : " << iterationCount << "\n"
                << "# Average Time         : " << results.avg() * secToMsec << " msec \n"
                << "# Minimum Time         : " << results.min() * secToMsec << " msec \n"
                << "# Maximum Time         : " << results.max() * secToMsec << " msec \n"
                << "# Standard Dev         : " << results.stddev() * secToMsec << " msec \n"
                << "# Quartiel Reg. 1      : " << results.q1() * secToMsec << " msec \n"
                << "# Median               : " << results.median() * secToMsec << " msec \n"
                << "# Quartiel Reg. 3      : " << results.q3() * secToMsec << " msec \n"
                << "#######################################################################\n\n";
        }

        file.close();
    }
}