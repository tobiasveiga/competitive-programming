/*
FARIDA - Princess Farida
https://www.spoj.com/problems/FARIDA/

Explanation:
- Uses inductive formula with DP
- The DP formula is simple, you either ignore the current monster or not
- f(i) = max(coins[i] + f(i) + 2, f(i+1))
- In the first param, we keep the coins of monster i and skip the next
- In the second param, we skip this monster and go to the next
- This solution is the iterative versions of the recursive funcition above

ACCEPTED
*/

#include <iostream>
#define i32 long
#define i64 long long

i32 T, N, coins[1'000];
i64 memo[1'000];

void solve() {
  memo[0] = coins[0];
  memo[1] = std::max((i64)coins[1], memo[0]);
  for (i32 i = 2; i < N; i++)
    memo[i] = std::max((i64)coins[i] + memo[i - 2], memo[i - 1]);
}

int main() {
  std::cin >> T;
  for (i32 t = 0; t < T; t++) {
    std::cin >> N;
    for (i32 i = 0; i < N; i++)
      std::cin >> coins[i];
    solve();
    auto ans = (N > 0 ? memo[N - 1] : 0);
    std::cout << "Case " << t + 1 << ": " << ans << "\n";
  }
  return 0;
}