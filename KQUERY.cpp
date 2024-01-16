/*
KQUERY - K-query
https://www.spoj.com/problems/KQUERY/

Explanation:
- Square Root Decomposition
- Each block contains a reference to a sub input array with sorted values
- Query all relevant blocks and sum all results
- If a query range intersect partially the block range, then use linear search
in the original input array
- Otherwise (fully intersection) use binary search in sub sorted array

ACCEPTED
*/
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define i32 long

i32 n, q, r, s, t;
i32 input[30'000], ans;
i32 aux[30'000], blk_size, n_blocks;

struct Block {
  i32 start, end;
  void init(i32 pos) {
    start = pos * blk_size;
    end = (pos + 1) * blk_size;
    end = (n < end ? n : end) - 1;
  }
  i32 query() {
    i32 count = 0;
    if (r > end || s < start) { // no intersection
      return count;
    }
    if (r > start || s < end) { // partial intersection
      for (i32 i = std::max(start, r); i <= std::min(end, s); i++)
        if (input[i] > t)
          count++;
      return count;
    } else { // full intersection
      i32 low = start, high = end, mid = (start + end) / 2;
      for (; low < high; mid = (low + high) / 2)
        if (aux[mid] <= t)
          low = mid + 1;
        else
          high = mid;
      count = (aux[end] <= t ? 0 : end - low + 1);
      return count;
    }
  }
} block[180];

void build() {
  blk_size = (i32)sqrt(n);
  n_blocks = 1 + (n - 1) / blk_size; // last block pos + 1
  for (i32 i = 0; i < n; i++)
    aux[i] = input[i];
  for (i32 i = 0; i < n_blocks; i++) {
    block[i].init(i);
    std::sort(aux + block[i].start, aux + block[i].end + 1);
  }
}
void solve() {
  ans = 0;
  for (i32 i = r / blk_size; i <= s / blk_size; i++) {
    ans += block[i].query();
  }
}

int main() {
  scanf("%ld", &n);
  for (i32 i = 0; i < n; i++)
    scanf("%ld", input + i);
  build();
  scanf("%ld", &q);
  for (i32 i = 0; i < q; i++) {
    scanf("%ld %ld %ld", &r, &s, &t);
    r--, s--;
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}