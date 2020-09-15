#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include "cv.hpp"
using namespace cv;
void f1(int n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread " << n << " executing\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void f2(int& n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
bool isrun = true;
void run()
{
	while (isrun)
	{
		std::cout << "run run run\n";
	}
	std::cout << "stop stop stop\n";
}
int main1111()
{
	//int n = 0;
	//std::thread t1; // t1 is not a thread
	//std::thread t2(f1, n + 1); // pass by value
	//std::thread t3(f2, std::ref(n)); // pass by reference
	//std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	//t2.join();
	//t4.join();
	//std::cout << "Final value of n is " << n << '\n';

	std::thread* thread_pImgGabber = new std::thread(run);
	thread_pImgGabber->detach();
	//thread_pImgGabber->join();
	delete thread_pImgGabber;

	while (true)
	{
		char ch;
		//(ch = std::cin.get());
		ch = getchar();
		std::cout << "Final value of n is " << ch<< '\n';
		if (ch == 'S' || ch == 's')
		{
			isrun = false;
			break;
		}
			
	}
	system("pause");
	return 0;
}