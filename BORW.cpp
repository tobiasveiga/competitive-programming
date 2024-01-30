/*
BORW - Black or White
https://www.spoj.com/problems/BORW/

DP induction function:
f(curr, prev_white, prev_black):=
f(N, prev_white, prev_black) = 0
f(curr, prev_white, prev_black) = min(
  f(curr+1, prev_white, curr) if X[curr] > X[prev_black]),
  f(curr+1, curr, prev_black) if X[curr] < X[prev_white]),
  1 + f(idx+1, prev_white, prev_black)
)

NOTE:
- all parameters are indexes in [0, N)
- prev_white and prev_black null value is N

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 N, X[200];

i32 memo[200][201][201];
const i32 INF = 1'000;

i32 f(i32 curr, i32 prev_white, i32 prev_black) {
  if (curr == N)
    return 0;
  if (memo[curr][prev_white][prev_black] != -1)
    return memo[curr][prev_white][prev_black];

  i32 temp = INF;
  if (X[curr] > X[prev_black] || prev_black == N)
    temp = std::min(temp, f(curr + 1, prev_white, curr));
  if (X[curr] < X[prev_white] || prev_white == N)
    temp = std::min(temp, f(curr + 1, curr, prev_black));
  temp = std::min(temp, 1 + f(curr + 1, prev_white, prev_black));

  memo[curr][prev_white][prev_black] = temp;
  return temp;
}

void solve() {
  memset(memo, -1, sizeof(memo));
  f(0, N, N);
}

int main() {
  while (true) {
    scanf("%ld", &N);
    if (N == -1)
      break;
    for (i32 i = 0; i < N; i++)
      scanf("%ld", X + i);
    solve();
    printf("%ld\n", memo[0][N][N]);
  }
  return 0;
}