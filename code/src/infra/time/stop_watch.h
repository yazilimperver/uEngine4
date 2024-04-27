/**
 * @file stop_watch.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief Modern C++ kabiliyetleri kullanarak zaman ölçmek için kullanılabilecek olan bir sınıf.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef STOPWATCH
#define STOPWATCH

#include <chrono>

/* @brief Namespace alias */
using ClockToUse = std::chrono::steady_clock;

class StopWatch {
public:   
   StopWatch();
   StopWatch(const StopWatch&);
   StopWatch& operator=(const StopWatch& rhs);

   /* @brief Referans zamanindan bu yana gecen mikrosaniyeyi doner. */
   uint64_t ElapsedUs() const;
   
   /* @brief Referans zamanindan bu yana gecen milisaniyeyi doner. */
   uint64_t ElapsedMs() const;

   /* @brief Referans zamanindan bu yana gecen saniyeyi doner. */
   uint64_t ElapsedSec() const;

   /* @brief  Sayacimiz sifirlar
    * @return Guncellenen referans zamanini donelim  */
   ClockToUse::time_point Restart();

private:
   /* @brief Referans zaman noktamızı tutalım. */
   ClockToUse::time_point mStart;
};

#endif // !STOPWATCH

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
