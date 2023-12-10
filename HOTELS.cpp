/*
HOTELS - Hotels Along the Croatian Coast
https://www.spoj.com/problems/HOTELS/

Solution:
- sliding window approach
- increment the sliding window by adding hotels to the right
- if the total value is exceeded remove hotels from the left until the condition
is satisfied (hence the sliding window can have length zero)

ACCEPTED
*/
#include <stdio.h>

#define i32 long
#define i64 long long

i32 get_max(i32 a, i32 b) { return (a > b ? a : b); }

i32 N, input[300'000];
i32 M, best;
i64 total; // total is at most M + 10**6, M being i32_MAX

int main() {
  scanf("%ld %ld", &N, &M);
  for (i32 i = 0; i < N; i++)
    scanf("%ld", input + i);

  best = -1;
  total = 0;
  for (i32 i = 0, j = 0; i < N; i++) {
    total += input[i];
    for (; total > M; j++)
      total -= input[j];
    best = get_max(best, (i32)total); // total here is at most M
  }

  printf("%ld\n", best);
}