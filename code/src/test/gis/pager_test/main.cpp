#include "gtest/gtest.h"

int main(int argc, char** argv) {
    // initialize
    ::testing::InitGoogleTest(&argc, argv);

    // run
    return RUN_ALL_TESTS();
}