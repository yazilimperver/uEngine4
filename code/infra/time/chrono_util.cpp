#include "chrono_util.h"

std::string ChronoUtil::ToString(const std::chrono::system_clock::time_point& tp) {
    // sistem zamanına dönüştürelim:
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    // takvimsel zamana dönüştürelim
    std::string ts = ctime(&t);

    // bunun sonuna eklenen yeni satır karakterini silelim
    ts.resize(ts.size() - 1);
    return ts;
}

void ChronoUtil::PrintThreeClockTypeInfo() {
    std::cout << std::boolalpha << "\n";

    std::cout << "std::chrono::system_clock: " << "\n";
    std::cout << "  is steady: " << std::chrono::system_clock::is_steady << "\n";
    ChronoUtil::PrintClockInfo<std::chrono::system_clock::period>();

    std::cout << "\n";

    std::cout << "std::chrono::steady_clock: " << "\n";
    std::cout << "  is steady: " << std::chrono::steady_clock::is_steady << "\n";
    ChronoUtil::PrintClockInfo<std::chrono::steady_clock::period>();

    std::cout << "\n";

    std::cout << "std::chrono::high_resolution_clock: " << "\n";
    std::cout << "  is steady: " << std::chrono::high_resolution_clock::is_steady << "\n";
    ChronoUtil::PrintClockInfo<std::chrono::high_resolution_clock::period>();
}

void ChronoUtil::PrintSystemClockInfo() {
    // Sistem saatinin, başlangıç zamanına bakalım
    std::chrono::system_clock::time_point tp;
    std::cout << "epoch: " << ChronoUtil::ToString(tp) << "\n";

    // Sistem saatinin mevcut anına bakalım
    tp = std::chrono::system_clock::now();
    std::cout << "now:   " << ChronoUtil::ToString(tp) << "\n";

    // Sistem saati ile ifade edilebilecek minimum zaman anına bakalım
    tp = std::chrono::system_clock::time_point::min();
    std::cout << "min:   " << ChronoUtil::ToString(tp) << "\n";

    // Sistem saati ile ifade edilebilecek maksimum zaman anına bakalım
    tp = std::chrono::system_clock::time_point::max();
    std::cout << "max:   " << ChronoUtil::ToString(tp) << "\n";
}

std::chrono::system_clock::time_point ChronoUtil::MakeTimePoint(int32_t year, int32_t mon, int32_t day, int32_t hour, int32_t min, int32_t sec) {
    struct std::tm t;
    t.tm_sec = sec;        // Saniye (0 .. 59)
    t.tm_min = min;        // Dakika (0 .. 59)
    t.tm_hour = hour;      // Saat (0 .. 23)
    t.tm_mday = day;       // Gün (0 .. 31)
    t.tm_mon = mon - 1;      // Ay (0 .. 11)
    t.tm_year = year - 1900; // 1900'den geçen sene
    t.tm_isdst = -1;       // Gün ışığını koruma var mı
    std::time_t tt = std::mktime(&t);

    if (tt == -1) {
        throw "Gecerli sistem zamani yok!";
    }
    return std::chrono::system_clock::from_time_t(tt);
}