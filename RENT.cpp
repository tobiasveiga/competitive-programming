#include <algorithm>
#include <stdio.h>
#define i32 long

i32 T, n, st, d, p;

struct Order {
  i32 st;
  i32 d;
  i32 p;
} order[10'001];

i32 dp[10'001];

i32 get_next(i32 idx) {
  auto end = order[idx].st + order[idx].d;
  // we want the first order with st >= end, i.e. lb(order, end);
  auto lb = std::lower_bound(order, order + n, end,
                             [](Order a, i32 key) { return a.st < key; });
  return lb - order; // lb is order+n if no such element exist;
}

i32 f(i32 idx) {
  if (idx >= n)
    return 0;
  if (dp[idx] != -1)
    return dp[idx];
  i32 temp = order[idx].p + f(get_next(idx));
  temp = std::max(temp, f(idx + 1));
  dp[idx] = temp;
  return temp;
}

int main() {
  scanf("%ld", &T);
  while (T--) {
    scanf("%ld", &n);
    for (i32 i = 0; i < n; i++) {
      scanf("%ld %ld %ld", &st, &d, &p);
      order[i] = {st, d, p};
    }
    std::sort(order, order + n, [](Order a, Order b) { return a.st < b.st; });
    for (i32 i = 0; i < n; i++)
      dp[i] = -1;
    printf("%ld\n", f(0));
  }
  return 0;
}