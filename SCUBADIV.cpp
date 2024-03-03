/*
SCUBADIV - Scuba diver
https://www.spoj.com/problems/SCUBADIV/

Explantion:
- DP with memo
- Recursive approach decreasing the value of oxygen and nitrogen, which are
capped at 0, avoiding segfault and allowing faster search

ACCEPTED
*/
#include <stdio.h>
#define i32 long
#include <string.h>

i32 tc, n, VO, VN, oi, ni, wi;
struct Cylinder {
  i32 vo;
  i32 vn;
  i32 w;
} c[1001];

i32 memo[1001][22][80];

i32 max(i32 a, i32 b) { return (a > b ? a : b); }

i32 f(i32 idx, i32 vo, i32 vn) {
  if (vo == 0 && vn == 0)
    return 0;
  if (idx >= n)
    return 800 * 1000 + 1;
  if (memo[idx][vo][vn] != 0)
    return memo[idx][vo][vn];
  auto no = f(idx + 1, vo, vn);
  auto yes =
      c[idx].w + f(idx + 1, max(0, vo - c[idx].vo), max(0, vn - c[idx].vn));
  auto temp = (no < yes ? no : yes);
  memo[idx][vo][vn] = temp;
  return temp;
}

int main() {
  scanf("%ld", &tc);
  while (tc--) {
    scanf("%ld %ld %ld", &VO, &VN, &n);
    for (i32 i = 0; i < n; i++)
      scanf("%ld %ld %ld", &(c[i].vo), &(c[i].vn), &(c[i].w));
    memset(memo, 0, sizeof(memo));
    printf("%ld\n", f(0, VO, VN));
  }
  return 0;
}