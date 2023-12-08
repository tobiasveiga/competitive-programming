/*
ARRAYSUB - subarrays
https://www.spoj.com/problems/ARRAYSUB/

Solution:
- creates a max value segtree
- run all sliding windows queries using the segtree

NOTE:
- in the problem it is stated the max n is 10'000 but only works with 10x that

ACCEPTED
*/
#include <stdio.h>

#define i32 long

i32 n, k, input[100'000];
const i32 MAX_NULL = -1;

i32 get_max(i32 a, i32 b) { return (a > b ? a : b); }

struct Segtree {
  i32 values[400'000];
  void build(i32 node, i32 x, i32 y) {
    if (x == y) {
      values[node] = input[x];
      return;
    }
    i32 z = (x + y) / 2;
    i32 left_node = node * 2 + 1;
    i32 right_node = node * 2 + 2;
    build(left_node, x, z);
    build(right_node, z + 1, y);
    values[node] = get_max(values[left_node], values[right_node]);
  }
  i32 query(i32 node, i32 x, i32 y, i32 r, i32 s) {
    if (x > s || y < r)
      return MAX_NULL;
    if (x >= r && y <= s)
      return values[node];
    i32 z = (x + y) / 2;
    i32 left_node = node * 2 + 1;
    i32 right_node = node * 2 + 2;
    return get_max(query(left_node, x, z, r, s),
                   query(right_node, z + 1, y, r, s));
  }
} segtree;

void solve() {
  for (i32 i = 0; i < n - k + 1; i++) {
    printf("%ld", segtree.query(0, 0, n - 1, i, i + k - 1));
    printf(" ");
  }
  return;
}

int main() {
  scanf("%ld", &n);
  for (i32 i = 0; i < n; i++)
    scanf("%ld", input + i);
  scanf("%ld", &k);
  segtree.build(0, 0, n - 1);
  solve();
  return 0;
}