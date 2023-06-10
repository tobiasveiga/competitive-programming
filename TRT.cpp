/*
TRT - Treats for the Cows
https://www.spoj.com/problems/TRT/

Explanation:
- Same problem as MIXTURES
- Straight forward DP using top down approach
- Use memoization to represent each subinterval
- The catch here is that AGE IS CONSTANT FOR EACH SUBINTERVAL
- For any subinterval from a to b, age is N - (b - a), -- counting from 0
- Therefore the memoization is just a 2D matrix

ACCEPTED
*/
#include <iostream>
#define i32 long

i32 N, value[2'000], memo[2'000][2'000], ans;

void reset() {
  for (i32 i = 0; i < N; i++)
    for (i32 j = 0; j < N; j++)
      memo[i][j] = -1;
}
i32 f(i32 x, i32 y) {
  if (memo[x][y] != -1)
    return memo[x][y];
  if (x == y) {
    memo[x][x] = N * value[x];
  } else {
    auto age = N - (y - x);
    memo[x][y] =
        std::max(age * value[x] + f(x + 1, y), age * value[y] + f(x, y - 1));
  }
  return memo[x][y];
}
void solve() { ans = f(0, N - 1); }
int main() {
  std::cin >> N;
  for (i32 i = 0; i < N; i++)
    std::cin >> value[i];
  reset();
  solve();
  std::cout << ans << "\n";
  return 0;
}