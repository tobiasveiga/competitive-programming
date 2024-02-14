/*
NGM - A Game with Numbers
https://www.spoj.com/problems/NGM/

Explanation:
- Closed formula solution
- The optimal strategy for each player is to remove the rightmost digit whenever
it is greater than 0
- The first player to do this wins

General example (Nikifor wins)
- Assume xi is the ith digit (from right to left) of a number x = [xn, ... x1]
with n digits
- First move - Given d = [dn,..,d1], d1 > 0 becomes d* = [dn,..., 0]
- Second move - d* becomes e = [en, ..., e1], e1 > 0
- The process repeats until the number is [0], which can only happen by the
first player who did the first move with d1 > 0

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 N;

int main() {
  while (scanf("%ld", &N) != EOF) {
    if (N % 10 > 0)
      printf("1\n%ld\n", N % 10);
    else
      printf("%d\n", 2);
  }
  return 0;
}