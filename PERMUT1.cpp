/*
PERMUT1 - Permutations
https://www.spoj.com/problems/PERMUT1/

Explanation:
- DP with memo
- Naive inductive function where f(N, K) is the answer is want
    f(n, 0) = 1
    f(1, k) = 0;
    f(n, k) = sum(f(n-1, i)), i in [max(0, k-n+1), k]
- The intuition is that as n grows, for each permutation of n-1 can have the
value n swapped at the exact position where the number of inversions become k,
by adding (n-position) inversions, given n is large enough
- The avove function repeatedly computes some values of f, total complexity
becomes O(n * k * k)
- If instead we compute the acummulated values of f(n, 0) to f(n, k), we have a
different function F
    F(n, 0) = 1
    F(n, k) = 0, k < 0
    F(1, k) = 1
    F(n, k) = F(n - 1, k) - F(n-1, k-n) + F(n, k - 1)
- And the answer is now F(N, K) - F(N, K-1), computed in O(n * k)

ACCEPTED
*/
#include <algorithm>
#include <stdio.h>
#define i32 long

i32 d, N, K;
i32 memo[13][99];

i32 f(i32 n, i32 k) { // the acummulated function F
  if (k == 0)
    return 1;
  if (k < 0)
    return 0;
  if (n == 1)
    return 1;
  if (memo[n][k] != 0)
    return memo[n][k];
  auto temp = f(n - 1, k) - f(n - 1, k - n) + f(n, k - 1);
  memo[n][k] = temp;
  return temp;
}
int main() {
  scanf("%ld", &d);
  while (d--) {
    scanf("%ld %ld", &N, &K);
    printf("%ld\n", f(N, K) - f(N, K - 1));
  }
  return 0;
}