/*
MULTQ3 - Multiples of 3
https://www.spoj.com/problems/MULTQ3/

Explanation:
- LazyProp approach - increments are lazyly stored
- Each node has a count for each %3 value in its range
- When a node is updated, instead of swaping the count, rotating the node count
array, we just update a pointer p pointing to the current position in the count
array where numbers are %3==0
- Parent nodes are updated by picking the correct count of each child and
adding them

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 N, Q, A, B, CMD, a[100'000];

struct SegTree {
  i32 cnt[400'000][3], p[400'000], lazy[400'000];
  void build(i32 idx, i32 x, i32 y) {
    if (x == y) {
      cnt[idx][0] = 1;
      return;
    }
    auto z = (x + y) / 2;
    auto left = idx * 2 + 1, right = idx * 2 + 2;
    build(left, x, z);
    build(right, z + 1, y);
    cnt[idx][0] = cnt[left][0] + cnt[right][0];
  }
  void lazy_prop(i32 idx, bool is_leaf) {
    if (lazy[idx] != 0) {
      if (!is_leaf) {
        lazy[idx * 2 + 1] += lazy[idx];
        lazy[idx * 2 + 2] += lazy[idx];
      }
      p[idx] = (p[idx] - lazy[idx] + 100'002) % 3;
      lazy[idx] = 0;
    }
  }
  void update(i32 idx, i32 x, i32 y, i32 value) {
    lazy_prop(idx, x == y);
    if (y < A || x > B)
      return;
    if (x >= A && y <= B) {
      lazy[idx] += value;
      lazy_prop(idx, x == y);
      return;
    }
    auto z = (x + y) / 2;
    auto left = idx * 2 + 1, right = idx * 2 + 2;
    update(left, x, z, value);
    update(right, z + 1, y, value);
    for (i32 i = 0; i < 3; i++) {
      auto l = cnt[left][(p[left] + i) % 3];
      auto r = cnt[right][(p[right] + i) % 3];
      cnt[idx][(p[idx] + i) % 3] = l + r;
    }
  }
  i32 query(i32 idx, i32 x, i32 y) {
    if (y < A || x > B)
      return 0;
    lazy_prop(idx, x == y);
    if (x >= A && y <= B)
      return cnt[idx][p[idx]];
    auto z = (x + y) / 2;
    return query(idx * 2 + 1, x, z) + query(idx * 2 + 2, z + 1, y);
  }
} segtree;

int main() {
  scanf("%ld %ld", &N, &Q);
  segtree.build(0, 0, N - 1);
  while (scanf("%ld %ld %ld", &CMD, &A, &B) != EOF) {
    if (CMD == 0)
      segtree.update(0, 0, N - 1, 1);
    else
      printf("%ld\n", segtree.query(0, 0, N - 1));
  }
  return 0;
}