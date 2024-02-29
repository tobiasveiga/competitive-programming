/*
CPCRC1C - Sum of Digits
https://www.spoj.com/problems/CPCRC1C/

Explanation:
- Iteratively DP approach
- f(x) = x * (x + 1) / 2, if x < 10 (single digit);
- f([d | y]) = f([d-1 | 9...9]) * + d * (y + 1) + f(y)
- example: f(345) = f(299) + 3 * (45+1) + f(45)
- notice that f(9...9) will always be needed
- in this approach f(9...9) is computed separately

ACCEPTED
*/
#include <stdio.h>
#define i32 long

i32 a, b;
i32 s(i32 n) {
  if (n <= 0)
    return 0;
  return (n * (n + 1)) / 2;
}
i32 f(i32 x) {
  i32 f_9s = 0; // f(9...9)
  i32 r = 1;    // helper to compute f(9...9)
  i32 ans = 0;
  for (i32 aux = x; aux > 0; aux /= 10) {
    auto d = aux % 10;
    auto y = x - (aux * r);
    auto c_9s = d * f_9s + s(d - 1) * r; // f([d-1 | 9...9]), c = d-1
    ans = c_9s + d * (y + 1) + ans;
    f_9s = f_9s * 10 + 45 * r;
    r *= 10;
  }
  return ans;
}

int main() {
  while (true) {
    scanf("%ld %ld", &a, &b);
    if (a == -1)
      break;
    printf("%ld\n", f(b) - f(a - 1));
  }
  return 0;
}