/**
 * @file active_object.h.
 * @date 11.03.2022
 * @author Yazilimperver
 * @brief  Ornek bir aktif nesne sınıfımız. Detaylar için https://www.state-machine.com/doc/Sutter2010a.pdf
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#pragma once

#include "data_structures/unbounded_shared_queue.h"
#include <functional>
#include <thread>
#include <iostream>
#include <memory>

// Temel aktif nesnemiz
class ActiveObject {
public:
    typedef std::function<void()> Message;

    ActiveObject();
    ~ActiveObject();
    void Send(Message m);
    
    ActiveObject(const ActiveObject&) = delete;
    void operator=(const ActiveObject&) = delete;
private:
    void Run();

    UnboundedSharedQueue<Message> mMessageQueue;
    std::unique_ptr<std::thread> mThread;
    bool mIsDone {false};
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
