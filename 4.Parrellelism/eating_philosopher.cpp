#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

#define N 5 // Number of philosophers

enum { THINKING, HUNGRY, EATING };

#define LEFT (ph_num + N - 1) % N
#define RIGHT (ph_num + 1) % N

mutex mtx;                      // Mutex for critical section
condition_variable cv[N];       // Condition variables for each philosopher
vector<int> state(N, THINKING); // States of each philosopher

void test(int ph_num) {
  if (state[ph_num] == HUNGRY && state[LEFT] != EATING &&
      state[RIGHT] != EATING) {
    state[ph_num] = EATING;
    cout << "Philosopher " << ph_num << " takes forks and is eating." << endl;
    cv[ph_num].notify_one();
  }
}

void take_fork(int ph_num) {
  unique_lock<mutex> lock(mtx);
  state[ph_num] = HUNGRY;
  cout << "Philosopher " << ph_num << " is hungry and tries to take forks."
       << endl;
  test(ph_num);
  while (state[ph_num] != EATING)
    cv[ph_num].wait(lock);
}

void put_fork(int ph_num) {
  unique_lock<mutex> lock(mtx);
  state[ph_num] = THINKING;
  cout << "Philosopher " << ph_num << " puts down forks and starts thinking."
       << endl;
  test(LEFT);  // Test if the left philosopher can eat
  test(RIGHT); // Test if the right philosopher can eat
}

void philosopher(int ph_num) {
  while (true) {
    sleep(1);
    take_fork(ph_num);
    sleep(0); // Eating
    put_fork(ph_num);
  }
}

int main() {
  vector<thread> philosophers;

  for (int i = 0; i < N; i++) {
    philosophers.push_back(thread(philosopher, i));
    cout << "Philosopher " << i << " is seated at the table." << endl;
  }

  for (auto &th : philosophers) {
    th.join();
  }

  return 0;
}
