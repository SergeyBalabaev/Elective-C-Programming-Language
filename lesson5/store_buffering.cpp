//g++ threads.cpp -o threads -lpthread

#include <thread>
#include <iostream>

void StoreBuffer(int i)
{
	int x = 0;
	int y = 0;

	int r1 = 0;
	int r2 = 0;

	std::thread t1([&]() {
		x = 1;
		r1 = y;
		});

	std::thread t2([&]() {
		y = 1;
		r2 = x;
		});

	t1.join();
	t2.join();

	if (r1 == 0 && r2 == 0) {
		std::cout << "Error on iteration " << i << std::endl;
		std::abort();
	}
}

int main()
{
	for (int i = 0; ; ++i)
		StoreBuffer(i);
	return 0;
}

