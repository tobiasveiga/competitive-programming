/*
ACPC10D - Tri graphs
https://www.spoj.com/problems/ACPC10D/

DP approach

ACCEPTED
*/
#include <queue>
#include <stdio.h>
#include <vector>
#define i32 long

i32 N, g[100'001][3];
i32 dp[100'001][3];
const i32 INF = 2e9;
const i32 option[][2] = {
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};
i32 f(i32 row, i32 col) {
  if (row == N - 1 && col == 1)
    return g[row][col];
  if (row == N)
    return INF;
  if (row == N - 1 && col == 2)
    return INF;
  if (dp[row][col] != INF)
    return dp[row][col];
  i32 temp = INF;
  for (auto op : option) {
    auto nrow = row + op[0];
    auto ncol = col + op[1];
    if (nrow < N && ncol >= 0 && ncol < 3) {
      auto curr = f(nrow, ncol);
      if (curr < temp)
        temp = curr;
    }
  }
  temp += g[row][col];
  dp[row][col] = temp;
  return temp;
}

int main() {
  i32 tc = 1;
  while (true) {
    scanf("%ld", &N);
    if (N == 0)
      break;
    for (i32 i = 0; i < N; i++)
      for (i32 j = 0; j < 3; j++)
        scanf("%ld", g[i] + j), dp[i][j] = INF;
    auto ans = f(0, 1);
    printf("%ld. %ld\n", tc, f(0, 1));
    tc++;
  }
  return 0;
}
