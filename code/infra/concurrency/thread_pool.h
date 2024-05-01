/**
 * @file thread_pool.h.
 * @date 8.05.2022
 * @author Yazilimperver
 * @brief BasicThreadPool sýnýfýnýn üzerine donus deðerini almaya yönelik kabiliyetleri eklediðimiz sýnýftýr.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include <future>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
	explicit ThreadPool(std::size_t threadCount = std::thread::hardware_concurrency());
	~ThreadPool();

	/** @brief Bunlarý kullanmayacaðýz */
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	ThreadPool& operator = (const ThreadPool&) = delete;
	ThreadPool& operator = (ThreadPool&&) = delete;

	/** @brief Gecirilecek is */
	using WorkItem = std::function<void(void)>;

	/** @brief Parametre almayan ve donus degeri olmayan isleri eklemek icin kullanilacak olan fonksiyon */
	template <typename W>
	void AddWork(const W& work) {
		std::scoped_lock guard(mQueueLock);
		mWorkItems.push(std::function<void()>(work));
		mTaskCV.notify_one();
	}

	/** @brief Parametre alan fakat donus degeri olmayan isleri eklemek icin kullanilacak olan fonksiyon
			   The function is wrapped inside a lambda in order to hide the arguments, as the tasks in the queue must be of type std::function<void()>, so they cannot have any arguments or return value. If no arguments are provided, the other overload will be used, in order to avoid the (slight) overhead of using a lambda. */
	template <typename W, typename... Args>
	void AddWork(const W& work, const Args&...params) {
		AddWork([work, params...]{ work(params...); });
	}

	/** @brief Parametre alan, donus degeri olmayan isleri eklemek icin kullanilacak olan fonksiyon
			   Donulen std::future ile isin bitip/bitmedigi kontrol edilebilir 
			   typename = ile baslayan kýsým aslýnda temelde bu fonksiyonun donus degeri void ise aktive olmasý, degilse bir sonrakinin aktive olmasýna yönelik bir kodtur! 
			   Daha detaylar icin cppreference ve SFINAE kavramlarýna göz atabiliriz */
	template <typename W, typename... Args, typename = std::enable_if_t<std::is_void_v<std::invoke_result_t<std::decay_t<W>, std::decay_t<Args>...>>>>
	std::future<bool> RequestWork(const W& work, const Args&...params) {
		std::shared_ptr<std::promise<bool>> task_promise(new std::promise<bool>);
		std::future<bool> future = task_promise->get_future();
		AddWork([work, params..., task_promise]
			{
				try {
					work(params...);
					task_promise->set_value(true);
				}
				catch (...) {
					try {

						task_promise->set_exception(std::current_exception());
					}
					catch (...) {
					}
				}
			});
		return future;
	}

	/** @brief Parametre alan ve donus degeri olan isleri eklemek icin kullanilacak olan fonksiyon
			   Donilen std::future ile isin bitip/bitmedigi kontrol edilebilir 
			   typename = ile baslayan kýsým aslýnda temelde bu fonksiyonun donus degeri void DEÐÝL ise aktive olmasý ve donus degeri tipinin de R'ye gecirilmesine yonelik bir kod!
			   Daha detaylar icin cppreference ve SFINAE kavramlarýna göz atabiliriz */
	template <typename W, typename... Args, typename R = std::invoke_result_t<std::decay_t<W>, std::decay_t<Args>...>, typename = std::enable_if_t<!std::is_void_v<R>>>
	std::future<bool> RequestWork(const W& work, const Args&...params) {
		std::shared_ptr<std::promise<R>> task_promise(new std::promise<R>);
		std::future<R> future = task_promise->get_future();
		AddWork([work, params..., task_promise]
			{
				try {
					work(params...);
					task_promise->set_value(true);
				}
				catch (...) {
					try {
						task_promise->set_exception(std::current_exception());
					}
					catch (...) {
					}
				}
			});
		return future;
	}

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
	size_t mThreadCount{ 0 };
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
