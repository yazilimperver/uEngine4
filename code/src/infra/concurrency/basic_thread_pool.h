/**
 * @file basic_thread_pool.h.
 * @date 8.05.2022
 * @author Yazilimperver
 * @brief Basit ve temel bir BasicThreadPool örneði
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include <functional>
#include <condition_variable>

class BasicThreadPool {
public:
	explicit BasicThreadPool(std::size_t threadCount = std::thread::hardware_concurrency());
	~BasicThreadPool();

	/** @brief Bunlarý kullanmayacaðýz */
	BasicThreadPool(const BasicThreadPool&) = delete;
	BasicThreadPool(BasicThreadPool&&) = delete;
	BasicThreadPool& operator = (const BasicThreadPool&) = delete;
	BasicThreadPool& operator = (BasicThreadPool&&) = delete;

	/** @brief Gecirilecek is */
	using WorkItem = std::function<void(void)>;

	/** @brief Parametre almayan ve donus degeri olmayan isleri eklemek icin kullanilacak olan fonksiyon */
	template <typename W>
	void AddWork(const W& work);
	
	/** @brief Parametre alan fakat donus degeri olmayan isleri eklemek icin kullanilacak olan fonksiyon 
			   The function is wrapped inside a lambda in order to hide the arguments, as the tasks in the queue must be of type std::function<void()>, so they cannot have any arguments or return value. If no arguments are provided, the other overload will be used, in order to avoid the (slight) overhead of using a lambda. */
	template <typename W, typename... Args>
	void AddWork(const W& work, const Args&...params);

	/** @brief Havuzda kac thread var? */
	size_t ThreadCount() const;

	/** @brief Threadpool'u baslatalim */
	void Start();
	
	/** @brief Hemen durduralim (islerin tamamlanmasini beklemeden) */
	void Stop();

	/** @brief Islerin tamamlanmasini bekleyelim */
	void WaitForCompletion();
private:
	using WorkItemQueue = std::queue<WorkItem>;

	/** @brief Thread pool'a gecirilen isleri tutar */
	WorkItemQueue mWorkItems;
	
	/** @brief Is kuyruguna guvenli erisim icin */
	std::mutex mQueueLock;
		
	/** @brief Verilen islerden thread'leri haberdar etmek icin */
	std::condition_variable mTaskCV;

	/** @brief Islerin tamamlanmasindan haberdar olmak icin kullanilacak */
	std::condition_variable mTasksCompletionCV;

	/** @brief Isleri gerceklestirecek thread'leri tutar */
	using threads_t = std::vector<std::thread>;
	threads_t mThreads;

	/** @brief Su an calisiyor muyuz */
	std::atomic<bool> mIsRunning{ true };
	
	/** @brief Mevcut thread sayisi */
	size_t mThreadCount{0};
};

template <typename W>
void BasicThreadPool::AddWork(const W& work) {
	std::scoped_lock guard(mQueueLock);
	mWorkItems.push(std::function<void()>(work));
	mTaskCV.notify_one();
}

template <typename W, typename... Args>
void BasicThreadPool::AddWork(const W& work, const Args&...params) {
	AddWork([work, params...]{ work(params...); });
}

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
