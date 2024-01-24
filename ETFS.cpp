/*
ETFS - Euler Totient Function Sieve
https://www.spoj.com/problems/ETFS/

Explanation:
- Similar solution to the problem ETF
- Instead of testing each possible prime < sqrt(n) for all n in the range [a,
b],
- for each prime, we got directly to the relevant values of n that n % prime ==
0, i.e. the pointer is updated like i += prime;
- then at each n % prime == 0 we compute the exponent of that prime in logp(n)
- so for each prime, p, the number of operation become O((b-a) / p * logp(n)),

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
#define i64 long long

i64 a, b;
const i32 N = (i32)1e7 + 1;
i64 phi[(i32)1e5];
i64 m[(i32)1e5];
bool notprime[N];
std::vector<i64> primes;

void compute_phi() {
  for (i64 i = a; i <= b; i++)
    phi[i - a] = 1, m[i - a] = i;
  for (auto p : primes) {
    if (p * p > b)
      break;
    for (i64 j = (a / p) * p; j <= b; j += p) {
      if (j < a) // too early
        continue;
      auto cnt = 0;
      while (m[j - a] % p == 0) {
        m[j - a] /= p;
        cnt++;
      }
      if (cnt > 0)
        phi[j - a] *= (i64)pow(p, cnt - 1) * (p - 1);
    }
  }
  for (i64 i = a; i <= b; i++)
    if (m[i - a] != 1)
      phi[i - a] *= (m[i - a] - 1);
}
void solve() {
  compute_phi();
  for (i64 i = a; i <= b; i++) {
    printf("%lld\n", phi[i - a]);
  }
}

void compute_primes() {
  for (i32 i = 2; i < N; i++) {
    if (!notprime[i])
      for (i32 j = i * i; j < N; j += i)
        notprime[j] = true;
  }
  for (i32 i = 2; i < N; i++)
    if (!notprime[i])
      primes.push_back(i);
}
int main() {
  compute_primes();
  while (scanf("%lld %lld", &a, &b) != EOF)
    solve();
  return 0;
}
