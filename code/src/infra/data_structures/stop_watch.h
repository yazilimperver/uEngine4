/**
 * @file StopWatch.h
 * @author yazılımperver
 * @brief Modern C++ kabiliyetleri kullanarak zaman ölçmek için kullanılabilecek olan bir sınıf.
 * @version 0.1
 * @date 2022-02-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <chrono>

/* @brief Namespace alias */
using ClockToUse = std::chrono::high_resolution_clock;

/* @brief Modern C++ kabiliyetleri kullanarak zaman ölçmek için kullanılabilecek olan bir sınıf. */
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