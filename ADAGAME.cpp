/*
ADAGAME - Ada and Game
https://www.spoj.com/problems/ADAGAME/

-- Explanation --
DP approach with Memoization
DP induction function:
f(num, 0, player) = ada if num > original
f(num, turns, player) =
  player if any(f(num+inc, turns-1, other) == player, for all inc in increments)
  else other player

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

#define ADA 0
#define VINIT 1

i32 T, M;
i32 N;
i32 memo[10'000][101][2];
char num_str[5];

i32 add_inc(i32 k) {
  auto temp = 0;
  for (i32 i = 0; i < 4; i++) {
    temp *= 10;
    if (i == k)
      temp += ((num_str[i] + 1) % 10);
    else
      temp += num_str[i];
  }
  return temp;
}

void break_num(i32 num) {
  i32 aux = num;
  for (i32 i = 0; i < 4; i++) {
    num_str[3 - i] = aux % 10;
    aux /= 10;
  }
}
i32 f(i32 num, i32 turns, i32 player) {
  if (turns == 0)
    return (num > N ? ADA : VINIT);
  if (memo[num][turns][player] != -1)
    return memo[num][turns][player];
  i32 temp = 1 - player;
  for (i32 i = 0; i < 4; i++) {
    break_num(num);
    i32 next_num = add_inc(i);
    i32 winner = f(next_num, turns - 1, 1 - player);
    if (winner == player) {
      temp = player;
      break;
    }
  }
  memo[num][turns][player] = temp;
  return temp;
}

void solve() {
  for (i32 i = 0; i < 10'000; i++)
    for (i32 j = 0; j <= M; j++)
      memo[i][j][0] = -1, memo[i][j][1] = -1;
  f(N, M, ADA);
}

int main() {
  scanf("%ld", &T);
  while (T--) {
    scanf("%ld %ld", &N, &M);
    solve();
    printf((memo[N][M][ADA] == ADA ? "Ada\n" : "Vinit\n"));
  }
  return 0;
}