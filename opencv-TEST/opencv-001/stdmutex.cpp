#include <thread>  
#include <mutex>
#include <time.h>
#include <stdio.h>  

std::mutex mutex1;
void print_msg(int arg) {
    int i = 0;
    
    for (i = 0; i<15; i++) {
        mutex1.lock();
        printf("Thread : %d output : %d\n", arg,i);
        mutex1.unlock();
    }
    
}
int mainstdmutex(int argc, char** argv) {
    std::thread id1(print_msg,1);
    std::thread id2(print_msg, 2);
    id1.join();
    id2.join();
    return 1;
}