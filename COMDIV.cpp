/*
COMDIV - Number of common divisors
https://www.spoj.com/problems/COMDIV/

Explanation:
- Decompose GCD
- Search is limited to primes between 2 and sqrt(GCD)

ACCEPTED
*/
#include <stdio.h>
#include <vector>
#define i32 long

i32 T, a, b;
std::vector<i32> primes;
bool notprime[1001];

i32 gcd(i32 a, i32 b) {
  if (a == 0)
    return b;
  return gcd(b % a, a);
}

int main() {

  for (i32 i = 2; i <= 1000; i++) {
    if (notprime[i])
      continue;
    for (i32 j = i * i; j <= 1000; j += i)
      notprime[j] = true;
  }
  for (i32 i = 2; i <= 1000; i++)
    if (!notprime[i])
      primes.push_back(i);

  scanf("%ld", &T);
  while (T--) {
    scanf("%ld %ld", &a, &b);
    i32 aux;
    i32 c = gcd(a, b);
    i32 ref = c;
    i32 total = 1;
    for (auto p : primes) {
      if (p * p > c)
        break;
      i32 curr = 1;
      while (c % p == 0)
        c /= p, curr++;
      total *= curr;
    }
    if (c != 1) // gcd has large prime
      total *= 2;
    printf("%ld\n", total);
  }
  return 0;
}