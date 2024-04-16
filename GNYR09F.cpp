#include <stdio.h>
#define i32 long

i32 TC, iTC, n, k, dp[101][101][2];

void reset() {
  for (i32 i = 0; i <= n; i++)
    for (i32 j = 0; j <= k; j++)
      dp[i][j][0] = -1, dp[i][j][1] = -1;
}
i32 f(i32 m, i32 l, i32 s) {
  // returns the ammount of times a string has k adjacent 1s
  // l counts the number of adjacents
  if (m == n && l == k && s == 0)
    return 1;
  if (m >= n)
    return 0;
  if (l > k)
    return 0; // early stoping
  if (dp[m][l][s] != -1)
    return dp[m][l][s];
  i32 temp = 0;
  if (s == 1)
    temp = f(m + 1, l, 0) + f(m + 1, l + 1, 1);
  else
    temp = f(m + 1, l, 0) + f(m + 1, l, 1);
  dp[m][l][s] = temp;
  return temp;
}

int main() {
  scanf("%ld", &TC);
  while (TC--) {
    scanf("%ld %ld %ld", &iTC, &n, &k);
    reset();
    printf("%ld %ld\n", iTC, f(0, 0, 0) + f(0, 0, 1));
  }
  return 0;
}