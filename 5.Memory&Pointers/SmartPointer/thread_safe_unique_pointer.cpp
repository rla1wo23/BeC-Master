#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

std::mutex mtx;

void threadFunc(std::unique_ptr<int> &ptr, int num) {
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "Hi, I'm " << "thread" << num << "\n";
  if (ptr) {
    std::cout << "thread " << num << " get the unique pointer!\nvalue:";
    std::unique_ptr<int> localPtr = std::move(ptr);
    std::cout << *localPtr << std::endl;
  } else {
    std::cout << "Pointer is already moved or null." << std::endl;
  }
}

int main() {
  std::unique_ptr<int> ptr = std::make_unique<int>(10);

  std::thread t1(threadFunc, std::ref(ptr), 1);
  std::thread t2(threadFunc, std::ref(ptr), 2);

  t1.join();
  t2.join();
}
