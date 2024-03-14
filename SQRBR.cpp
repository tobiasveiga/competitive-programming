/*
SQRBR - Square Brackets
https://www.spoj.com/problems/SQRBR/

Explanation:
- DP
- Induction function f(x, o) below
- x := index in the sequece
- o := number of opening brackets so far, also c := num. closing brackets

    f(x, o) = 0 if c > o, or o > n, (c := x - o)
    f(2n, o) = 1
    f(x, o) = f(x+1, o + 1), if x in list
    f(x, o) = f(x+1, o + 1) + f(x+1, o)

ACCEPTED
*/
#include <stdio.h>
#define i32 long

const i32 N = 20, K = 20;
i32 d, n, k, s;

bool strict[2 * N];
i32 dp[2 * N][K];

i32 f(i32 x, i32 o) {
  if ((x - o) > o)
    return 0;
  if (o > n)
    return 0;
  if (x == 2 * n)
    return 1;
  if (dp[x][o] != -1)
    return dp[x][o];

  i32 temp = f(x + 1, o + 1) + (strict[x] ? 0 : f(x + 1, o));
  dp[x][o] = temp;
  return temp;
}

int main() {

  scanf("%ld", &d);
  while (d--) {

    scanf("%ld %ld", &n, &k);

    for (i32 i = 0; i <= 2 * n; i++)
      for (i32 j = 0; j <= n; j++)
        dp[i][j] = -1;
    for (i32 i = 0; i <= 2 * n; i++)
      strict[i] = false;

    for (i32 i = 0; i < k; i++) {
      scanf("%ld", &s);
      strict[s - 1] = true;
    }

    auto ans = f(0, 0);
    printf("%ld\n", ans);
  }

  return 0;
}