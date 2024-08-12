// problem from boj_12738
// solution for find maximum length of LIS in O(n*logn) time
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int N, cnt;
int arr[1000001];
vector<int> v;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> N;
  for (int i = 0; i < N; i++)
    cin >> arr[i];
  v.push_back(arr[0]);
  int v_idx = 0;
  for (int i = 1; i < N; i++) {
    if (v[v_idx] < arr[i]) {
      v.push_back(arr[i]);
      v_idx++;
    } else {
      int target = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
      v[target] = arr[i];
    }
  }
  cout << v.size();
}