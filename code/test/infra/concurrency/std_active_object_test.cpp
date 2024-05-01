#include <thread>
#include <chrono>

#include "gtest/gtest.h"

#include "concurrency/std_active_object.h"

TEST(StdActiveObject, StdActiveObjectShouldBeInitializedCorrectly) {
    // Class under test
    StdActiveObject CUTInstance;

    ASSERT_TRUE(CUTInstance.IsActive());
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 0);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 0);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 0);
    ASSERT_EQ(CUTInstance.ObtainOneShotTimers().size(), 0);
}

TEST(StdActiveObject, SingleEventShouldBeProcessed_LambdaFunction) {
    StdActiveObject CUTInstance;

    int result = 0;
    CUTInstance.PostEvent([&result]() {
        result = 65;
        });
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 1);

    // Biraz bekleyelim
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 0);

    ASSERT_EQ(result, 65);
}

int globalValueToUse = 0;
void StandaloneFunctionWithNoArgument() {
    globalValueToUse = 65;
}

TEST(StdActiveObject, SingleEventShouldBeProcessed_StandAloneFunctionWithNoArgument) {
    StdActiveObject CUTInstance;

    CUTInstance.PostEvent(StandaloneFunctionWithNoArgument);
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 1);

    // Biraz bekleyelim
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 0);

    ASSERT_EQ(globalValueToUse, 65);
}

void StandaloneFunctionWithArgument(int& input) {
    input = 65;
}

TEST(StdActiveObject, SingleEventShouldBeProcessed_StandAloneFunctionWithArgument) {
    StdActiveObject CUTInstance;

    int result = 0;
    CUTInstance.PostEvent(StandaloneFunctionWithArgument, result);
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 1);

    // Biraz bekleyelim
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 0);

    ASSERT_EQ(result, 65);
}

class ClassExample {
    int value{ 0 };
public:
    void EventHandler() {
        value = 99;
    }

    int Value() const {
        return value;
    }
};

TEST(StdActiveObject, SingleEventShouldBeProcessed_ClassMember) {
    StdActiveObject CUTInstance;

    ClassExample instance;

    CUTInstance.PostEvent(&ClassExample::EventHandler,&instance);
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 1);

    // Biraz bekleyelim
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(CUTInstance.ObtainTaskQueue().size(), 0);

    ASSERT_EQ(instance.Value(), 99);
}

TEST(StdActiveObject, PeriodicTimerEventShouldCallGivenEventHandlerPeriodically) {
    StdActiveObject CUTInstance;

    int counter = 0;

    // 50 ms'de bir calistirilacak bir is verelim
    CUTInstance.PostPeriodicTimerEvent([&counter]() {
        ++counter;
        }, std::chrono::milliseconds(50));

    std::this_thread::sleep_for(std::chrono::milliseconds(250)); 

    CUTInstance.Stop();

    EXPECT_GE(counter, 5);
}

TEST(StdActiveObject, PeriodicTimerHandlerCanBeUsedToStopGivenTimer) {
    StdActiveObject CUTInstance;

    int counter = 0;

    // 50 ms'de bir calistirilacak bir is verelim
    auto timerHandle = CUTInstance.PostPeriodicTimerEvent([&counter]() {
        ++counter;
        }, std::chrono::milliseconds(50));

    ASSERT_EQ(0, timerHandle);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 1);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CUTInstance.StopPeriodicTimer(timerHandle);
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 

    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 0);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 0);

    CUTInstance.Stop();

    EXPECT_GE(counter, 2);
}

TEST(StdActiveObject, PeriodicTimersShouldBeStoppable) {
    StdActiveObject CUTInstance;

    int counter1 = 0;
    int counter2 = 0;

    // 50 ms'de bir calistirilacak bir is verelim
    auto timerHandle = CUTInstance.PostPeriodicTimerEvent([&counter1]() {
        ++counter1;
        }, std::chrono::milliseconds(50));

    ASSERT_EQ(0, timerHandle);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 1);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 1);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // 50 ms'de bir calistirilacak bir is verelim
    timerHandle = CUTInstance.PostPeriodicTimerEvent([&counter2]() {
        ++counter2;
        }, std::chrono::milliseconds(100));

    ASSERT_EQ(1, timerHandle);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 2);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 2);

    // Bir iki tur donmelerine izin verelim
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    EXPECT_GE(counter1, 15);
    EXPECT_GE(counter2, 10);
    CUTInstance.Stop();

    // Bekleme, en uzun periyot suresine sahip sayac kadar olmali
    std::this_thread::sleep_for(std::chrono::milliseconds(110));
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimers().size(), 0);
    ASSERT_EQ(CUTInstance.ObtainPeriodicTimerStopFlags().size(), 0);

}