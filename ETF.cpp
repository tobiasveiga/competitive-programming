/*
ETF - Euler Totient Function
https://www.spoj.com/problems/ETF/

Explanation:
- Pre-compute all primes up to 1000
- Factorize the number into the factor primes and exponent
- Factorization is done by iterating over precomputed primes up to sqrt(n)
- A auxiliar variable m, starts at n and is updated by dividing by each factor
found
- If after all iterations, m!=1, then there was one prime factor, m, grater than
sqrt(n)
- Then we take all the prime factor and exponents and apply to the Eulers
product formula


ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int T;
i32 n;
i32 ans;

const i32 P = 1'001; // max prime search, last idx == 1'000
bool sieve[P];
std::vector<i32> primes;

struct Factor {
  i32 prime;
  i32 count;
};
std::vector<Factor> factors;

void build() {
  for (i32 i = 2; i < P; i++) {
    if (sieve[i])
      continue;
    for (i32 j = i * i; j < P; j += i)
      sieve[j] = true;
  }
  for (i32 i = 2; i < P; i++)
    if (!sieve[i])
      primes.push_back(i);
}

void solve() {
  factors.clear();
  auto m = n;
  for (auto p : primes) {
    if (p * p > n)
      break;
    if (m % p == 0) {
      auto cnt = 0;
      while (m > 0 && m % p == 0) {
        m /= p;
        cnt++;
      }
      factors.push_back({p, cnt});
    }
  }
  if (m != 1)
    factors.push_back({m, 1});
  ans = 1;
  for (auto f : factors)
    ans *= (i32)pow(f.prime, f.count - 1) * (f.prime - 1);
}

int main() {
  build();
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}