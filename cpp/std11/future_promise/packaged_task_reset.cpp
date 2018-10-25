// http://www.cplusplus.com/reference/future/packaged_task/reset/
#include <iostream>     // std::cout
#include <utility>      // std::move
#include <future>       // std::packaged_task, std::future
#include <thread>       // std::thread
// 

// a simple task:
int triple (int x) { return x*3; }

int main ()
{
    std::packaged_task<int(int)> tsk (triple); // package task


    std::future<int> fut = tsk.get_future();
    std::thread (std::ref(tsk), 100).detach();
    // https://www.cnblogs.com/haippy/p/3279565.html
    // 后面出错是必然的，std::thread (std::move(tsk), 100).detach();已经将tsk的控制权转移了，tsk 到了后面已经是无效的了， 
    std::cout << "The triple of 100 is " << fut.get() << ".\n";


    // re-use same task object:
    tsk.reset();
    // tsk.reset()调用会操作指针，指针已经为空了，所以崩溃，
    // 详细用法可以参考：www.cplusplus.com/reference/future/packaged_task/reset/
    fut = tsk.get_future();
    std::thread(std::move(tsk), 200).detach();
    std::cout << "Thre triple of 200 is " << fut.get() << ".\n";

    return 0;
}
