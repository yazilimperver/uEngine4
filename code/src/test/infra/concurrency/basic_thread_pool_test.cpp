#include <thread>
#include <chrono>

#include "time/stop_watch.h"

#include "gtest/gtest.h"
#include "concurrency/basic_thread_pool.h"

TEST(BasicThreadPool, ThreadPoolCorrectInitialization) {
	BasicThreadPool instance;
	ASSERT_EQ(instance.ThreadCount(), std::thread::hardware_concurrency());
}

TEST(BasicThreadPool, ZeroThreadCountShouldThrow) {
	ASSERT_THROW(BasicThreadPool{ 0 }, std::invalid_argument);
}


TEST(BasicThreadPool, OneThreadUsageShoulNotReduceTotalTime) {
	StopWatch stopWatch;

	constexpr auto timeToWaitInMsec = 200;
	constexpr auto threadCount = 1;
	constexpr auto workCount = 20;

	{
		BasicThreadPool instance{ threadCount };
		instance.Start();

		for (auto i = 1; i <= workCount; i++)
			instance.AddWork([&, id = i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(timeToWaitInMsec));
				});
	} // Stop'suz threadpool tamamlanmasini bekleyelim

	auto elapsedTime = stopWatch.ElapsedMs();

	ASSERT_GE(elapsedTime, timeToWaitInMsec * workCount);
}

TEST(BasicThreadPool, ThreadPoolUsageShouldReduceTotalTime) {
	StopWatch stopWatch;

	constexpr auto timeToWaitInMsec = 200;
	constexpr auto workCount = 20;
	
	BasicThreadPool instance;
	instance.Start();
	
	for (auto i = 1; i <= workCount; i++)
		instance.AddWork([&, id = i]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(timeToWaitInMsec));
			});

	// Stop ile threadpool tamamlanmasini bekleyelim
	instance.WaitForCompletion();

	auto elapsedTime = stopWatch.ElapsedMs();

	ASSERT_LT(elapsedTime, timeToWaitInMsec* workCount);
}

TEST(BasicThreadPool, ThreadPoolAddTaskWithNoParamNoRetunValueTest) {
	StopWatch stopWatch;

	constexpr auto workCount = 20;
	
	bool taskCompletionStatuses[workCount] = { false };

	BasicThreadPool instance;
	instance.Start();

	for (auto i = 0; i < workCount; ++i)
		instance.AddWork([&, slotIndex = i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(rand()%500));
			taskCompletionStatuses[slotIndex] = true;
			});

	// Stop ile threadpool tamamlanmasini bekleyelim
	instance.WaitForCompletion();

	auto elapsedTime = stopWatch.ElapsedMs();

	for (auto i = 0; i < workCount; ++i) {
		ASSERT_TRUE(taskCompletionStatuses[i]) << " Index: " << i;
	}
}

TEST(BasicThreadPool, ThreadPoolAddTaskWithOneParamNoRetunValueTest) {
	StopWatch stopWatch;

	constexpr auto workCount = 20;

	bool taskCompletionStatuses[workCount] = { false };

	BasicThreadPool instance;
	instance.Start();

	for (auto i = 0; i < workCount; ++i)
		instance.AddWork([&](int slotIndex) {
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500));

			// gecirilecek olan parametreyi ataylim
			taskCompletionStatuses[slotIndex] = true; }
			, i);

	// Stop ile threadpool tamamlanmasini bekleyelim
	instance.WaitForCompletion();

	auto elapsedTime = stopWatch.ElapsedMs();

	for (auto i = 0; i < workCount; ++i) {
		ASSERT_TRUE(taskCompletionStatuses[i]) << " Index: " << i;
	}
}

TEST(BasicThreadPool, ThreadPoolAddTaskWithTwoParamNoRetunValueTest) {
	StopWatch stopWatch;

	constexpr auto workCount = 20;

	bool taskCompletionStatuses[workCount] = { false };

	BasicThreadPool instance;
	instance.Start();

	// 0, 2, ... elemanlari true yap
	for (auto i = 0; i < workCount; ++i)
		instance.AddWork(
			// Is kalemi
			[&](int slotIndex, bool slotValue) {
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500));

				// gecirilecek olan parametreyi ataylim
				taskCompletionStatuses[slotIndex] = slotValue; 
			},
			// Ilk arguman
			i, 
			// Ikinci argumen
			(i%2) == 0);

	// Stop ile threadpool tamamlanmasini bekleyelim
	instance.WaitForCompletion();

	auto elapsedTime = stopWatch.ElapsedMs();

	for (auto i = 0; i < workCount; ++i) {
		ASSERT_EQ(taskCompletionStatuses[i], (i%2)==0) << " Index: " << i;
	}
}