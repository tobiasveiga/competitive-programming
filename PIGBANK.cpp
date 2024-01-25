/*
PIGBANK - Piggy-Bank
https://www.spoj.com/problems/PIGBANK/

-- EXPLANATION --
DP approach
Inductive function:
>> f(weight) = min(coin.value + f(weight - coin.weight) for coin in coins)
>> f(weight) = INF, weight < 0   // A fail node in the DP tree
>> f(0) = 0;                     // A success node in the DP tree

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int T, E, F, N, P, W;
i32 ans;

struct Coin {
  i32 value;
  i32 weight;
};
std::vector<Coin> coins;

i32 memo[10'001];
const i32 INF = (i32)1e9;

i32 f(i32 weight) {
  if (weight == 0)
    return 0;
  if (weight < 0)
    return INF;
  if (memo[weight] != 0)
    return memo[weight];
  i32 best = INF;
  for (auto coin : coins) {
    auto temp = f(weight - coin.weight);
    if (temp == INF)
      continue;
    best = std::min(best, coin.value + temp);
  }
  memo[weight] = best;
  return best;
}
void solve() {
  memset(memo, 0, (F - E + 1) * sizeof(i32));
  ans = f(F - E);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    coins.clear();
    scanf("%d %d %d", &E, &F, &N);
    for (int i = 0; i < N; i++)
      scanf("%d %d", &P, &W), coins.push_back({P, W});
    solve();
    if (ans == INF)
      printf("This is impossible.\n");
    else
      printf("The minimum amount of money in the piggy-bank is %ld.\n", ans);
  }
  return 0;
}