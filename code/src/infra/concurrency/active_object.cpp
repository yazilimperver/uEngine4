#include "active_object.h"
#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "spdlog/spdlog.h"
#pragma warning( pop )

inline ActiveObject::ActiveObject() {
    mThread = std::unique_ptr<std::thread>(
        new std::thread([=] { this->Run(); }));
}

inline ActiveObject::~ActiveObject() {
    Send([&] { mIsDone = true; });


    spdlog::trace("Aktif nesne yokedilecek. Once butun islerin tamamlanmasini bekliyoruz!\n");
    mThread->join();
    spdlog::trace("Aktif nesne yokedildi!\n");
}

inline void ActiveObject::Send(Message m) {
    mMessageQueue.Push(m);
}

inline void ActiveObject::Run() {
    spdlog::trace("Aktif nesne yaratildi ve baslatildi. Mesajlari bekliyoruz!\n");
    Message msg;

    while (!mIsDone) {
        mMessageQueue.Pop(msg);

        msg();
    }
}
