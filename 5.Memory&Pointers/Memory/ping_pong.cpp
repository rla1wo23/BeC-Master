#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// 스레드 간 통신을 위한 전역 변수
std::queue<std::string> message_queue;
std::mutex mtx;
std::condition_variable cv;

void pinger() {
  for (int i = 0; i < 5; ++i) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)); // 대기 시간 추가
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Sending ping..." << std::endl;
    message_queue.push("ping");
    cv.notify_one(); // 대기 중인 소비자 스레드에 알림
  }
}

void printer() {
  for (int i = 0; i < 5; ++i) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] {
      return !message_queue.empty();
    }); // 메시지가 들어올 때까지 대기

    std::string msg = message_queue.front();
    message_queue.pop();
    lock.unlock();

    std::cout << "Received: " << msg << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기
  }
}

int main() {
  // 스레드 생성
  std::thread t1(pinger);
  std::thread t2(printer);

  // 스레드들이 작업을 끝낼 때까지 대기
  t1.join();
  t2.join();

  return 0;
}
