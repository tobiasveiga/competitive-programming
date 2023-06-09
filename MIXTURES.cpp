/*
MIXTURES - Mixtures
https://www.spoj.com/problems/MIXTURES/

Explanation:
- Straight forward Top Down DP approach
- Initially the problem might appears confusing if one assumes we must optimize
for both color and smoke
- The important thing is to understand that the color of any sequence of
mixtures is always the same
- Therefore, we just have to minimize the smoke for each node in the recursion
tree

ACCEPTED
*/
#include <iostream>
#include <tuple>
#define i32 long

i32 T, N, mix[100], smoke[100][100], color[100][100], ans;

void reset() {
  for (i32 i = 0; i < N; i++)
    for (i32 j = 0; j < N; j++)
      smoke[i][j] = -1;
}
void get(i32 a, i32 b) {
  if (smoke[a][b] != -1)
    return;
  if (a == b) {
    smoke[a][a] = 0;
    color[a][a] = mix[a];
    return;
  }
  i32 lowest_smoke = __LONG_MAX__;
  i32 best = -1;
  i32 left, right;
  for (i32 i = a; i < b; i++) {
    get(a, i);
    get(i + 1, b);
    left = color[a][i];
    right = color[i + 1][b];
    auto total_smoke = left * right + smoke[a][i] + smoke[i + 1][b];
    if (total_smoke < lowest_smoke) {
      best = i;
      lowest_smoke = total_smoke;
    }
  }
  smoke[a][b] = lowest_smoke;
  color[a][b] = (left + right) % 100;
}
void solve() {
  get(0, N - 1);
  ans = smoke[0][N - 1];
}
int main() {
  while (scanf("%ld", &N) != EOF) {
    for (i32 i = 0; i < N; i++)
      std::cin >> mix[i];
    reset();
    solve();
    std::cout << ans << "\n";
  }
  return 0;
}