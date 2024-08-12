#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v = {1, 3, 5, 7};
  int target = 2;
  // lower bound part
  auto lower = std::lower_bound(v.begin(), v.end(), target);

  if (lower != v.end()) {
    std::cout << "Lower bound for " << target
              << " is at position: " << std::distance(v.begin(), lower)
              << std::endl;
    std::cout << "Value at lower bound: " << *lower << std::endl;
  } else {
    std::cout << "No element found that is greater than or equal to " << target
              << std::endl;
  }
  // upper bound part
  auto upper = std::upper_bound(v.begin(), v.end(), target);

  if (upper != v.end()) {
    std::cout << "Upper bound for " << target
              << " is at position: " << std::distance(v.begin(), upper)
              << std::endl;
    std::cout << "Value at upper bound: " << *upper << std::endl;
  } else {
    std::cout << "No element found that is greater than " << target
              << std::endl;
  }

  return 0;
  return 0;
}
