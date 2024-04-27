#include "thread_pool.h"

ThreadPool::ThreadPool(std::size_t threadCount) {
	if (!threadCount)
		throw std::invalid_argument("Thread adeti sifir olmamali!");
	mThreadCount = threadCount;
	mThreads.reserve(mThreadCount);
}

ThreadPool::~ThreadPool() {
	if (mThreads.size() > 0)
		WaitForCompletion();
}

size_t ThreadPool::ThreadCount() const {
	return mThreadCount;
}

void ThreadPool::Start() {
	for (auto i = 0; i < mThreadCount; ++i) {
		mThreads.push_back(std::thread([this]() {
			while (mIsRunning) {
				WorkItem work;

				{
					std::unique_lock guard(mQueueLock);
					// Yeni bir is icin bekleyelim
					mTaskCV.wait(guard, [&]() { return (!mWorkItems.empty() || !mIsRunning); });

					if (mIsRunning) {
						work = mWorkItems.front();
						mWorkItems.pop();
					}
				}

				// Isi gerceklestir
				if (mIsRunning)
					(work)();

				// Isigin bittigini haberdar edelim
				mTasksCompletionCV.notify_one();
			}
			}));
	}
}

void ThreadPool::Stop() {
	mIsRunning = false;
	mTaskCV.notify_all();

	// Islerin bitmesini bekleyelim
	for (auto& t : mThreads)
		t.join();

	mThreads.clear();
}

void ThreadPool::WaitForCompletion() {
	{
		std::unique_lock guard(mQueueLock);
		mTasksCompletionCV.wait(guard, [&]() { return mWorkItems.empty(); });
	}
	Stop();
}
