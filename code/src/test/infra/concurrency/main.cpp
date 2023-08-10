/*
#include "concurrency/basic_thread_pool.h"
#include <iostream>

int main()
{
	using namespace std;
	srand(time(NULL));
	mutex cout_guard;

	std::cout << "main thread ID: " << this_thread::get_id() << endl;

	BasicThreadPool tp;
	tp.Start();

	for (auto i = 1; i <= 50; i++)
		tp.EnqueueWork([&, i = i]()
			{
				{
					unique_lock guard(cout_guard);
					std::cout << "doing work " << i << "..." << endl;
				}
				this_thread::sleep_for(chrono::milliseconds(rand() % 1000));
			});
	tp.WaitForCompletion();
}*/

#include "gtest/gtest.h"

int main(int argc, char** argv) {
    // initialize
    ::testing::InitGoogleTest(&argc, argv);

    // run
    return RUN_ALL_TESTS();
}