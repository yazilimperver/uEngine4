// Orjinal yazı için: https://www.yazilimperver.com/index.php/2020/11/09/haftalik-c-33-zaman-bilgisi-etiketi/
// For original post: https://www.yazilimperver.com/index.php/2020/11/09/haftalik-c-33-zaman-bilgisi-etiketi/
#pragma once

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
