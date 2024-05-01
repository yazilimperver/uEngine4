/**
 * @file chrono_util.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief  Kod'a iliskin detaylar icin https://www.yazilimperver.com/index.php/2021/08/16/haftalik-c-39-stdchrono-2-clocks-time_point/
 *         Ozetle, zamanla ilgili kullanacağımız bazı faydalı fonksiyonları toplayacağımız sınıftır
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef CHRONOUTILS
#define CHRONOUTILS

#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>

class ChronoUtil {
public:
   // timepoint nesnelerimizi time_t tipine, onu da takvimsel saat gösterimine (ör. Mon May 23 13:44:00 2011), çevirmek için kullanacağımız fonksiyondurdur
    static std::string ToString (const std::chrono::system_clock::time_point& tp);
    
    // Takvimsel zaman bilgilerinden, sistem saatinin time_point nesnesine çevirmek için kullanabileceğimi fonksiyondur
    static std::chrono::system_clock::time_point MakeTimePoint (int32_t year, int32_t mon, int32_t day,
                   int32_t hour, int32_t min, int32_t sec = 0);

    // Uc tip saat tipinin sonuclarini gosterir
    static void PrintThreeClockTypeInfo();

    // Sistem saatine iliskin bilgileri basalim
    static void PrintSystemClockInfo();

    // Saati şablon parametresi olarak geçirelim
    template <typename T>
    static void PrintClockInfo(){ 
        std::cout << "  precision: " << T::num << "/" << T::den << " second " << "\n";
        typedef typename std::ratio_multiply<T,std::kilo>::type MillSec;
        typedef typename std::ratio_multiply<T,std::mega>::type MicroSec;
        std::cout << std::fixed;
        std::cout << "             " << static_cast<double>(MillSec::num)/MillSec::den << " milliseconds "   << "\n";
        std::cout << "             " << static_cast<double>(MicroSec::num)/MicroSec::den << " microseconds " << "\n";
    }  
};

#endif // !CHRONOUTILS

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
