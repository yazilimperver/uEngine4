#include "gtest/gtest.h"

#include "time/timer.h"
#include "time/threaded_timer.h"
#include "time/stop_watch.h"

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    
    /*
    // initialize
    ::testing::InitGoogleTest(&argc, argv);

    // run
    return RUN_ALL_TESTS();*/

    constexpr unsigned int intervalInMsec = 1;
    constexpr unsigned int count = 100;
    uint64_t samples[count+10];
    int index = 0;

    ThreadedTimer t;

    StopWatch timeToTrack;
    t.SetInterval([&timeToTrack, &samples, &index]() {
        samples[index++] = timeToTrack.ElapsedMs();
        }, intervalInMsec);

    ThreadedTimer t2;
    t2.SetTimeout([&]() {
        cout << "Hey.. After " << (count * intervalInMsec) / 1000.0 << "s. But I will stop the timer!" << endl;
        t.Stop();

        cout << "Olcumler: ";
        for (size_t i = 1; i < count; i++) {
            cout << samples[i] - samples[i - 1] << ", ";
        }
        cout << "\n";
        }, (count + 1) * intervalInMsec);

    cout << "Tamamlanmasini bekleyelim!\n";
    t2.WaitForCompletion();
    cout << "Tamamlandi!\n";

    return 0;
}