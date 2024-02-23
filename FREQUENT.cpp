/*
FREQUENT - Frequent values
https://www.spoj.com/problems/FREQUENT/

Explanation:
- Segtree approach
- Leverages on the input sorted order
- Merging two nodes max is just the max of the two nodes if their merging values
are not the same
- Otherwise we need the new count of the merged value and update the max if
necessary
- This implementation keeps a counter for both the leftmost and righmost value
of each node, which simplifies the merge operation

ACCEPTED
*/
#include <algorithm>
#include <stdio.h>
#define i32 long

const i32 N = 100'000;
i32 n, q, input[N], a, b;
i32 max(i32 a, i32 b) { return (a > b ? a : b); }
i32 min(i32 a, i32 b) { return (a < b ? a : b); }
struct Node {
  i32 best;
  i32 lcnt;
  i32 rcnt;
  Node merge(Node right, i32 x, i32 y, i32 z) {
    Node temp = {max(best, right.best), lcnt, right.rcnt};
    if (input[z] == input[z + 1]) {
      temp.best = max(rcnt + right.lcnt, temp.best);
      if (input[x] == input[z])
        temp.lcnt = lcnt + right.lcnt;
      if (input[y] == input[z])
        temp.rcnt = rcnt + right.rcnt;
    }
    return temp;
  }
} node[4 * N];

void build(i32 idx, i32 x, i32 y) {
  if (x == y) {
    node[idx] = {1, 1, 1};
    return;
  }
  auto z = (x + y) / 2;
  build(idx * 2 + 1, x, z);
  build(idx * 2 + 2, z + 1, y);
  node[idx] = node[idx * 2 + 1].merge(node[idx * 2 + 2], x, y, z);
}

Node query(i32 idx, i32 x, i32 y) {
  if (x > b || y < a)
    return {0, 0, 0};
  if (x >= a && y <= b)
    return node[idx];
  auto z = (x + y) / 2;
  auto left = query(idx * 2 + 1, x, z);
  auto right = query(idx * 2 + 2, z + 1, y);
  auto temp = left.merge(right, max(x, a), min(y, b), z);
  return temp;
}

int main() {
  while (true) {
    scanf("%ld", &n);
    if (n == 0)
      break;
    scanf("%ld", &q);
    for (i32 i = 0; i < n; i++)
      scanf("%ld", input + i);
    build(0, 0, n - 1);
    for (i32 i = 0; i < q; i++) {
      scanf("%ld %ld", &a, &b);
      a--, b--;
      auto ans = query(0, 0, n - 1);
      printf("%ld\n", ans.best);
    }
  }
  return 0;
}