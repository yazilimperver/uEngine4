// example_app.cpp : Defines the entry point for the application.
//

#include "example_app.h"
#include "data_structures/bounded_shared_queue.h"
#include "concurrency/active_object.h"
#include "concurrency/thread_base.h"
#include "time/sleep_util.h"

#include "spdlog/spdlog.h"

#include "graphics/color.h"

#include "application_base/touch_service.h"

#include <nlohmann/json.hpp>
using nlohmann::json;

#include <cstdint>
#include <chrono>

using namespace std;

#include "SDL.h" 

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/*
int main() {
	//CBoundedSharedQueue<int> deneme{ 10 };
	cout << "Hello uEngine 4." << endl;
	return 0;
}

*/
/*


class Backgrounder {
public:
    void Save(std::string filename) {
        using namespace std::chrono_literals;
        mActiveObject.Send([=]{ 
            std::cout <<"Dosya <" << filename <<"> kayit isi basladi!\n";
            std::this_thread::sleep_for(2000ms);
            std::cout <<"Dosya  <" << filename <<"> kayit isi bitti!\n";
            } );
    }
    void Print(std::string data) {
        using namespace std::chrono_literals;
        mActiveObject.Send([=]{ 
            std::cout <<"Ekrana bastirilacak olan mesaj: " << data << "\n";            
            std::this_thread::sleep_for(500ms);
            } );
    }

private:
    // Burada ayrica bu aktif nesneye spesifik veriler tutulabilir
    // ...

    // Aktif nesnemiz
    ActiveObject mActiveObject;
};

int main() {
    Backgrounder backActiveObject;
    backActiveObject.Save("BuyukDosya1.bin");
    backActiveObject.Save("BuyukDosya2.bin");
    backActiveObject.Print("Merhaba dostum!");
    std::cout <<"Normal sartlarda 4.5 sn sonra bunu gormeniz lazimdi!\n";
    std::cout <<"Ama uygulama kapanmadan butun islerin tamamlanmasini bekleyecegiz!\n";

    return 0;
}
*/
/*
class TimerTest : public ThreadBase {
    double mSleepTimeInSec{ 10.0 };
public:
    TimerTest(double sleepTime)
        : mSleepTimeInSec(sleepTime) {
    };
protected:
    virtual void ThreadEntryFunc() {
        using namespace std;
        using namespace std::chrono;

        auto prevClock = high_resolution_clock::now();
        while (true) {
            auto nextClock = high_resolution_clock::now();
            double deltaTime = (nextClock - prevClock).count() / 1e9;
            printf(" frame time for %f sec: %.2lf ms\n", mSleepTimeInSec, deltaTime * 1e3);
            SleepUtil::PreciseSleep(mSleepTimeInSec);
            prevClock = nextClock;
        }
    }
};

int main() {
    Color deneme{255, 0, 0};

    spdlog::debug("[example_app] Application is started!");

    TimerTest instance1(1 / 10000.0);
    instance1.Start();
    int i;
    std::cin >> i;
}*/