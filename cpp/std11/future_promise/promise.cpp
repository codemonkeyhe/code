/*
https://wizardforcel.gitbooks.io/cpp-11-faq/content/70.html
https://en.cppreference.com/w/cpp/thread/promise

https://en.cppreference.com/w/cpp/thread/promise/promise
promise( promise&& other ) noexcept; (3) (since C++11)
3) Move constructor. Constructs the promise with the shared state of other using move semantics. 
After construction, other has no shared state. 构造完之后，other就是个废物了，没有shared state了

promise( const promise& other ) = delete; (4) (since C++11)
4) promise is not copyable.
因此不可以用作函数参数的复制传参，只能用移动构造函数来传参
 
*/

#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
 
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // Notify future
}
 
void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}
 
int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                            std::move(accumulate_promise));
    accumulate_future.wait();  // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // wait for thread completion
 
    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
}
