/*
LITE - Light Switching
https://www.spoj.com/problems/LITE/

Explanation:
- Segtree + Lazyprop approach
- The lazy update of any node is either 0 or 1
- A real node is only updated if lazy == 1, then the new value becomes the node
range size - previous value

ACCEPTED
*/
#include <stdio.h>
#define i32 long

i32 N, M, op, a, b;

struct Segtree {
  i32 real[4 * 100'000];
  i32 lazy[4 * 100'000];
  void inc_node(i32 curr) { lazy[curr] = (lazy[curr] + 1) % 2; }
  void lazy_prop(i32 curr, i32 n) {
    if (lazy[curr] == 0)
      return;
    if (n != 1) { // curr is not leaf
      inc_node(curr * 2 + 1);
      inc_node(curr * 2 + 2);
    }
    real[curr] = n - real[curr];
    lazy[curr] = 0;
  }
  void add(i32 curr, i32 x, i32 y) {
    lazy_prop(curr, y - x + 1);
    if (a > y || b < x)
      return;
    if (a <= x && b >= y) {
      inc_node(curr);
      lazy_prop(curr, y - x + 1);
      return;
    }
    auto z = (x + y) / 2;
    add(curr * 2 + 1, x, z);
    add(curr * 2 + 2, z + 1, y);
    real[curr] = real[curr * 2 + 1] + real[curr * 2 + 2];
  }
  i32 query(i32 curr, i32 x, i32 y) {
    if (a > y || b < x)
      return 0;
    lazy_prop(curr, y - x + 1);
    if (a <= x && b >= y)
      return real[curr];
    auto z = (x + y) / 2;
    return query(curr * 2 + 1, x, z) + query(curr * 2 + 2, z + 1, y);
  }
} segtree;

int main() {
  scanf("%ld %ld", &N, &M);
  while (scanf("%ld %ld %ld", &op, &a, &b) != EOF) {
    a--, b--;
    if (op == 0)
      segtree.add(0, 0, N - 1);
    else
      printf("%ld\n", segtree.query(0, 0, N - 1));
  }
  return 0;
}