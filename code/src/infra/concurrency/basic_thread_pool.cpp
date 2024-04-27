#include "basic_thread_pool.h"

BasicThreadPool::BasicThreadPool(std::size_t threadCount) {
	if (!threadCount)
		throw std::invalid_argument("Thread adeti sifir olmamalidir!");
	mThreadCount = threadCount;
	mThreads.reserve(mThreadCount);
}

BasicThreadPool::~BasicThreadPool() {
	if (mThreads.size() > 0)
		WaitForCompletion();
}

size_t BasicThreadPool::ThreadCount() const {
	return mThreadCount;
}

void BasicThreadPool::Start() {
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

void BasicThreadPool::Stop() {
	mIsRunning = false;
	mTaskCV.notify_all();

	// Islerin bitmesini bekleyelim
	for (auto& t : mThreads)
		t.join();

	mThreads.clear();
}

void BasicThreadPool::WaitForCompletion() {
	{
		std::unique_lock guard(mQueueLock);
		mTasksCompletionCV.wait(guard, [&]() { return mWorkItems.empty(); });
	}
	Stop();
}
