/*
WILLITST - Will it ever stop
https://www.spoj.com/problems/WILLITST/

Explanation:
- Any number n is of the form 3 ** p * 2 ** q * r, r being any other prime
factorization of primes other than 2 or 3, p and q being non negative int.
- If n is even we get 3 ** p * 2 ** (q - 1) * r
- Otherwise we get 3 ** (p + 1) * ((2 ** q * r) + 1)
- The loop ends if n <= 1, which only happens if
  p==0 and r==1 because they never decrease.
- Hence this solution checks if the n == 2 ** q.

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
#define i64 long long

i64 n;

int main() {
  while (scanf("%lld", &n) != EOF) {
    i32 cnt = 0;
    for (i64 m = n; m > 0; m >>= 1)
      if (m & 1ll)
        cnt++;
    if (cnt <= 1)
      printf("TAK\n");
    else
      printf("NIE\n");
  }
  return 0;
}