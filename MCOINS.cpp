/*
MCOINS - Coins Game
https://www.spoj.com/problems/MCOINS/

Explanation:
- Iterative approach for DP problem
- We need one option for player A, in which next player B has no
option (2nd turn option), which implies all of his next options are A winning

  f(0) = true, i.e. A wins
  f(n) = any(all(f(n - op - op2) for op2 in options) for op in options),
  s.t. n - op - op2 >= 0 and n - op >= 0

ACCEPTED
*/
#include <stdio.h>
#define i32 long

i32 m, K, L, N;
bool ans[50];
bool dp[1'000'001];

void solve() {
  const i32 options[] = {1, K, L};
  dp[0] = true;
  for (i32 i = 1; i <= 1'000'000; i++) {
    bool any = false;
    for (const auto op : options) {
      if (i - op < 0)
        continue;
      bool all = true;
      for (const auto op2 : options) {
        if (i - op - op2 < 0)
          continue;
        all = all && dp[i - op - op2] && (i - op - op2 != 0);
      }
      any = any || all;
    }
    dp[i] = any;
  }
}

int main() {
  scanf("%ld %ld %ld", &K, &L, &m);
  solve();
  for (i32 i = 0; i < m; i++)
    scanf("%ld", &N), ans[i] = dp[N];
  for (i32 i = 0; i < m; i++)
    printf("%c", (ans[i] ? 'A' : 'B'));
  printf("\n");
}