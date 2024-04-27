#include "timestamp.h"

// Asagida ihtiyac duyuacaginiz baslik dosyalarini görebilirsiniz
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

// Çok basit bir şekilde Epoch anindan bu yana geçen zamanı milisaniye cinsinden almak için
uint64_t Timestamp::getTimestampInMsec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

// Bu da mevcut zamanı daha güzel ifade etmek icin stringe çeviren bir metot
std::string Timestamp::getTimeString() {
	using namespace std::chrono;
	system_clock::time_point p = system_clock::now();
	std::time_t t = system_clock::to_time_t(p);

	// ref: http://www.cplusplus.com/reference/ctime/ctime/
	std::string result = std::ctime(&t);

	return result;
}

// Bu fonksiyon biraz daha sayisal ve kayıtlar icin uygun bir format sunuyor bizlere
// Format şu şekilde "2020-11-09 20:19:45.217"
std::string Timestamp::getDetailedTimeString() {
	using namespace std::chrono;

	// Mevcut zamanı alalım
	auto now = system_clock::now();

	// Milisaniyeye çevirelim
	auto timeInMsec = duration_cast<milliseconds>(now.time_since_epoch()).count();

	// Zaman bilgisi içerisinde ilgili saniyeye ilişkin artık milisaniyeyi göstermek için
	// kalanı bulalım
	auto ms = timeInMsec % 1000;

	// Elimizdeki zaman bilgisini time_t formatına çevirelim
	std::time_t timer = system_clock::to_time_t(now);

	// İlgili zamanı yerel zamana çevirelim
	std::tm bt = *std::localtime(&timer);

	// String'e çevirmek için string akış sınıfını kullanalım
	std::ostringstream oss;

	// Diger format seçenekleri için https://en.cppreference.com/w/cpp/io/manip/put_time
	oss << std::put_time(&bt, "%F %H:%M:%S"); // HH:MM:SS

	// Artık milisaniyeyi de ekleyelim
	oss << '.' << std::setfill('0') << std::setw(3) << ms;

	return oss.str();
}

// Bu fonksiyon bir önceki metodun aynısını verilen zaman için yapıyor. Özellikle çeşitli kanallar aracılığı
// ile edindiğiniz zaman bilgisini görselleştirmek için faydalı olabilir
std::string Timestamp::getDetailedTimeString(uint64_t msec) {
	using namespace std::chrono;

	// Mevcut zamanı alalım
	auto now = system_clock::now();

	// Milisaniyeye çevirelim
	auto timeInMsec = msec;

	// Zaman bilgisi içerisinde ilgili saniyeye ilişkin artık milisaniyeyi göstermek için
	// kalanı bulalım
	auto ms = timeInMsec % 1000;

	// Elimizdeki zaman bilgisini time_t formatına çevirelim
	std::time_t timer = static_cast<std::time_t>(timeInMsec / 1000);

	// İlgili zamanı yerel zamana çevirelim
	std::tm bt = *std::localtime(&timer);

	// String'e çevirmek için string akış sınıfını kullanalım
	std::ostringstream oss;

	// Diger format seçenekleri için https://en.cppreference.com/w/cpp/io/manip/put_time
	oss << std::put_time(&bt, "%F %H:%M:%S"); // HH:MM:SS

	// Artık milisaniyeyi de ekleyelim
	oss << '.' << std::setfill('0') << std::setw(3) << ms;

	return oss.str();
}
