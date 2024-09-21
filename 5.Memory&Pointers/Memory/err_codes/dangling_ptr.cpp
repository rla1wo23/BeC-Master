#include <iostream>
#include <unistd.h>
int main() {
  int *ptr = (int *)malloc(sizeof(int));
  int *bad_ptr = ptr;
  *ptr = 10;
  free(ptr);
  sleep(10);
  std::cout << *ptr;
}