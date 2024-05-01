#include "thread_base.h"

ThreadBase::~ThreadBase() {
    mIsThreadActive.store(false);

    if (nullptr != mThread) {
        if (mThread->joinable()) {
            mThread->join();
        }
    }
}

void ThreadBase::Stop() {
    mIsThreadActive.store(false);
}

void ThreadBase::Start() {
    //	printf("Thread is started!\n");
    mThread = std::make_unique<std::thread>(&ThreadBase::ThreadEntryFunc, this);
}

void ThreadBase::WaitForCompletion() {
    mThread->join();
}