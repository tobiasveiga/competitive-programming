/*
CANTON - Count on Cantor
https://www.spoj.com/problems/CANTON/

Explanation:

No closed formula, use binary search

ith [1, ...] diagonal has i elements
up to the ith diagonal there are 1 + 2 + ... + i elements
total(i) = (1 + i) * i / 2 = (i + i*i) / 2
and one diagonal before that are total(i) - i

For any number term, the argmin(total(diag)), total(diag) >= term, indicates in
which diagonal the term is in other words we want LowerBound(term, total)
Wich will give diag, counting starting from 1

If diagnoal is even
Then the term starting at init = total(diag-1) + 1, will be 1 / diag
Then delta = term - init provide the solution (1 + delta) / (diag - delta)

If diagonal is odd
Do the same but solution = (diag - delta) / (1 + delta)

ACCEPTED
*/
#include <stdio.h>
#define i32 long

const i32 N = 10'000;
i32 t, term;

i32 diag, init, delta, num, den;

i32 total(i32 i) { return (i + i * i) / 2; }

void solve() {
  i32 low = 1, high = 10'000, mid = 10'001 / 2;
  for (; low < high; mid = (low + high) / 2)
    if (total(mid) < term)
      low = mid + 1;
    else
      high = mid;
  diag = low;
  init = total(diag - 1) + 1;
  delta = term - init;
  if (diag % 2 == 0)
    num = 1 + delta, den = (diag - delta);
  else
    num = (diag - delta), den = 1 + delta;
}

int main() {
  scanf("%ld", &t);
  while (t--) {
    scanf("%ld", &term);
    solve();
    printf("TERM %ld IS %ld/%ld\n", term, num, den);
  }
  return 0;
}