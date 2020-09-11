#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{
    
    // create thread pool with 4 worker threads
    ThreadPool pool1(4);

    // enqueue and store future
    auto result = pool1.enqueue([](int answer) { return answer + 1; }, 42);

    // get result from future
    std::cout << result.get() << std::endl;

    std::cout <<"=============="<<std::endl;


    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}