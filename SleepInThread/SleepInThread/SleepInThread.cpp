// SleepInThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<thread>
#include<mutex>
#include<iostream>
std::mutex mtx;
bool g_flag = false;
void F1(int n)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        n++;
        if (n == 10) 
        {
            mtx.lock();
            g_flag = true;
            mtx.unlock();
        }
        else
            std::cout << "F1 n: " << n << std::endl;
    }
}

void F2(int& n)
{
    while (true)
    {
        mtx.lock();
        bool flag = g_flag;
        mtx.unlock();
        if (flag)
        {
            n++;
            std::cout << "F2 n: " << n << std::endl;
        }
        else
            std::this_thread::yield();
    }
}
int main()
{
    int n = 0;
    std::thread t1(F1, n), t2(F2, std::ref(n));
    t1.join();
    t2.join();
    //char *str = (char*)malloc(100);
    //strcpy_s(str,6,"hello");
    //free(str);
    //if (str != nullptr)
    //{
    //    strcpy_s(str,6, "world");
    //    printf(str);
    //}
    return 0;
}
  
