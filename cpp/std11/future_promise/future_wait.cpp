/*
http://www.cplusplus.com/reference/future/future/wait/

void wait() const;
Wait for ready
Waits for the shared state to be ready.
If the shared state is not yet ready (i.e., the provider has not yet set its value or exception), the function blocks the calling thread and waits until it is ready.
Once the shared state is ready, the function unblocks and returns without reading its value nor throwing its set exception (if any).

All visible side effects are synchronized between the point the provider makes the shared state ready and the return of this function.

*/

// future::wait
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds

// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  // call function asynchronously:
  std::future<bool> fut = std::async(is_prime,194232491); 

  std::cout << "checking...\n";
  fut.wait();

  std::cout << "\n194232491 ";
  if (fut.get())      // guaranteed to be ready (and not block) after wait returns
    std::cout << "is prime.\n";
  else
    std::cout << "is not prime.\n";

  return 0;
}
