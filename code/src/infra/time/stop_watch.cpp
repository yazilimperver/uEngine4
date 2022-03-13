#include "stop_watch.h"
#include "spdlog/spdlog.h"

using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using seconds =  std::chrono::seconds;

StopWatch::StopWatch()
    : mStart(ClockToUse::now()) {
   static_assert(std::chrono::steady_clock::is_steady, "OS/C++ chrono steady clock ile ilgili bir sikinti mevcut!");
}

StopWatch::StopWatch(const StopWatch& other)
    : mStart(other.mStart) { 
}

StopWatch& StopWatch::operator=(const StopWatch& rhs) {
      mStart = rhs.mStart;
      return *this;
}

uint64_t StopWatch::ElapsedUs() const {
   return std::chrono::duration_cast<microseconds>(ClockToUse::now() - mStart).count();
}

uint64_t StopWatch::ElapsedMs() const {
   return std::chrono::duration_cast<milliseconds>(ClockToUse::now() - mStart).count();
}

uint64_t StopWatch::ElapsedSec() const {
   return std::chrono::duration_cast<seconds>(ClockToUse::now() - mStart).count();
}

std::chrono::steady_clock::time_point StopWatch::Restart() {
   mStart = ClockToUse::now();
   return mStart;
}