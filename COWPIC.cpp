/*
COWPIC - Cow Photographs
https://www.spoj.com/problems/COWPIC/
ACCEPTED
*/
#include <iostream>
#include <math.h>
#define i32 long
#define i64 long long

using namespace std;

i32 N, input[100'001], aux[100'001], num2Pos[100'001];
i64 ans, inversions;

void buildNum2Pos() {
  for (i32 i = 1; i <= N; i++)
    num2Pos[input[i]] = i;
}
void mergesort(i32 low, i32 high) {
  if (low == high)
    return;
  i32 mid = low / 2 + high / 2;
  mergesort(low, mid);
  mergesort(mid + 1, high);
  for (i32 k = low, i = low, j = mid + 1; k <= high; k++) {
    if (i > mid | (j <= high && input[j] < input[i])) {
      aux[k] = input[j++];
      inversions += (mid - i + 1);
    } else
      aux[k] = input[i++];
  }
  for (i32 i = low; i <= high; i++)
    input[i] = aux[i];
}
i32 getInversionDelta(i32 num) {
  i32 prev =
      num2Pos[num] - 1; // how many numbers are before when num is the smallest
  i32 next =
      N - num2Pos[num]; // how many number are after when num is the largest
  return next - prev;
}
void solve() {
  buildNum2Pos();
  inversions = 0;
  mergesort(1, N);
  ans = INT64_MAX;
  for (i32 i = 1; i < N; i++) { // stop before N to avoid cycle
    inversions += getInversionDelta(i);
    ans = std::min(ans, inversions);
  }
}

int main() {
  std::cin >> N;
  for (long i = 1; i <= N; i++)
    std::cin >> input[i];
  solve();
  std::cout << ans << std::endl;
  return 0;
}