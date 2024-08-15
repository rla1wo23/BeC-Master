#include <iostream>
int main() {
  std::cout << "Input Float number to print" << "\n";
  float num;
  std::cin >> num;
  std::cout << "original output:" << num;
  std::cout << "It will output up to N decimal places. Enter N.\n";
  int N;
  std::cin >> N;
  std::cout << std::fixed;
  std::cout.precision(N);
  std::cout << num;
}