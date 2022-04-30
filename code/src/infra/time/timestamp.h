/**
 * @file timestamp.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief Anlik zamana iliskin bilgi almaya yonelik yardimci fonksiyonlari icerisinde barindiran siniftir
 *  	  Orjinal yazı için: https://www.yazilimperver.com/index.php/2020/11/09/haftalik-c-33-zaman-bilgisi-etiketi/
 *		  For original post: https://www.yazilimperver.com/index.php/2020/11/09/haftalik-c-33-zaman-bilgisi-etiketi/
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */

#ifndef TIMESTAMP
#define TIMESTAMP

#include <cstdint>
#include <string>

class Timestamp {
public:
	// Basit bir şekilde Epoch anindan bu yana geçen zamanı milisaniye cinsinden almak için
	static uint64_t getTimestampInMsec();

	// Asagidaki fonksiyon mevcut zamanı (Tue Sep 27 14:21:13 2011) formatında doner
	static std::string getTimeString();

	// Bu fonksiyon, mevcut zaman bilgisini biraz daha sayısal ve kayıtlar icin uygun bir formatta sunuyor bizlere
	// Format şu şekilde "2020-11-09 20:19:45.217"
	static std::string getDetailedTimeString();

	// Bu fonksiyon bir önceki metodun aynısını verilen zaman için yapıyor. Özellikle çeşitli kanallar aracılığı
	// ile edindiğiniz zaman bilgisini görselleştirmek için faydalı olabilir
	static std::string getDetailedTimeString(uint64_t msec);
};


#endif // !TIMESTAMP

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
