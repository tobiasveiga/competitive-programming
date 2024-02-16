/*
TWENDS - Two Ends
https://www.spoj.com/problems/TWENDS/

Explanation:
- DP with memo
- Induction function is f(x, y), which returns the max sum for the first
player
- x:= start idx, y:= end idx
- Answer becomes the cards total sum minus the first player max points

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 n, input[1'000];
i32 memo[1'000][1'000], ans;

i32 f(i32 x, i32 y) {
  if (x == y)
    return 0;
  if ((y - x) % 2 == 0) // odd elements - greedy turn
    return (input[x] >= input[y] ? f(x + 1, y) : f(x, y - 1));
  if (memo[x][y] != -1)
    return memo[x][y];
  auto temp = std::max(input[x] + f(x + 1, y), input[y] + f(x, y - 1));
  memo[x][y] = temp;
  return temp;
}

void solve() {
  for (i32 i = 0; i < n; i++)
    for (i32 j = 0; j < n; j++)
      memo[i][j] = -1;
  f(0, n - 1);
  i32 total = 0;
  for (i32 i = 0; i < n; i++)
    total += input[i];
  ans = 2 * memo[0][n - 1] - total;
}

int main() {
  i32 tc = 1;
  while (scanf("%ld", &n) != EOF) {
    if (n == 0)
      break;
    for (i32 i = 0; i < n; i++)
      scanf("%ld", input + i);
    solve();
    printf("In game %ld, the greedy strategy might lose by as many as %ld "
           "points.\n",
           tc++, ans);
  }
  return 0;
}