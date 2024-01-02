/*
EKO - Eko
https://www.spoj.com/problems/EKO/

Explanation:
- Uses binary search on the cutting height space
- Cutting height spaces range is [1, max(tree)]
- Evaluation at each iteration checks whether there is at least M cut off wood

ACCEPTED
*/
#include <stdio.h>

#define i32 long
#define i64 long long

i32 N, M, tree[1'000'000];

i32 max(i32 a, i32 b) { return (a > b ? a : b); }

bool eval(i32 height) {
  i64 total = 0;
  for (i32 i = 0; i < N; i++) {
    total += max(0, tree[i] - height);
    if (total >= M)
      return true;
  }
  return false;
}

void solve() {
  i32 low = 1;
  i32 high = -1;
  for (i32 i = 0; i < N; i++)
    high = max(high, tree[i]);
  i32 mid = (low + high) / 2;
  while (low < high) {
    if (eval(mid)) {
      low = mid + 1;
    } else {
      high = mid;
    }
    mid = (low + high) / 2;
  }
  // Assumes there is always an answer
  printf("%ld\n", low - 1);
}

int main() {
  scanf("%ld %ld", &N, &M);
  for (i32 i = 0; i < N; i++)
    scanf("%ld", tree + i);
  solve();
  return 0;
}