/*
FIBOSUM - Fibonacci Sum
https://www.spoj.com/problems/FIBOSUM/

Explanation:
- We use the fact that
        >> SUM(F(n)) = F(n+2) - 1
- Our solution then becomes
        >> SUM(F(M)) - SUM(F(N-1)) =
        >> [F(M+2) - 1] - [F(N+1) - 1] = F(M+2) - F(N+1)
- Since n can be in a wide range of values, we need to compute F(n) at query
time
- We can compute any F(n) with integer numbers only using the matrix closed
formula
        >> [[F(n+1), F(n)], [F(n), F(n-1)]] = [[1, 1], [1, 0]]**n = fibo_mat**n
- fibo_mat**n can be computed using a log(n) exponentiation by squaring approach
- We precompute all fibo_mat**n, n=2**i, i = 0, ... i = 31
- So if n = 9, n=(2**3 + 2**1), we just use
        >> fibo_mat**9 =  fibo_mat**(2**3) *fibo_mat**(2**1)
- Regarding the mod operation, we only use addition and multiplication, so we
just apply mod after these operations ocurr

ACCEPTED
*/
#include <math.h>
#include <stdio.h>

#define i32 long
#define i64 long long
#define f64 long double

i32 T, N, M;
const i32 X = 1'000'000'007l;
struct FiboMatrix {
  i64 fn;
  i64 fn_next;
  i64 fn_prev;
  FiboMatrix mult(FiboMatrix other) {
    return {(fn_next * other.fn + fn * other.fn_prev) % X,
            (fn_next * other.fn_next + fn * other.fn) % X,
            (fn * other.fn + fn_prev * other.fn_prev) % X};
  }
} power2[32];
// fn_next  fn
// fn       fn_prev

void build() {
  power2[0] = {1, 1, 0};
  for (i32 i = 1; i < 32; i++)
    power2[i] = power2[i - 1].mult(power2[i - 1]);
}

i32 get_fibo_mod(i32 n) {
  if (n <= 0)
    return 0;
  FiboMatrix fibo_mat = {0, 1, 1}; // identity matrix
  for (i32 bits = n, i = 0; bits > 0; bits >>= 1, i++) {
    if (bits & 1l)
      fibo_mat = fibo_mat.mult(power2[i]);
  }
  return fibo_mat.fn;
}

i32 solve() { return (get_fibo_mod(M + 2) - get_fibo_mod(N - 1 + 2) + X) % X; }

int main() {
  build();
  scanf("%ld", &T);
  while (T--) {
    scanf("%ld %ld", &N, &M);
    printf("%ld\n", solve());
  }
  return 0;
}