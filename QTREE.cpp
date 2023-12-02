/*
QTREE - Query on a tree
https://www.spoj.com/problems/QTREE/

Solution:
- Very straight forward solution, uses High Low Density tree data structure.
- The query consists of climbing the heavy paths for both nodes until they are
both in the same heavy path
- We always climb with the node, which the heavy path head has greater depth
- By doing so we guarantee that when both nodes reach the same heavy path, one
will be the LCA and the other will be a LCA descendant in the same path.
- Everytime we climb, we compute the max from the edges in the climbed path and
update the overall max value
- Updating an edge just update the corresponding value in the segment tree, so
there is nothing special

ACCEPTED
*/
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define i32 long
#define i64 long long

#define MAX_N 10'000

struct Segtree {
  i32 value[MAX_N * 4];
  i32 input[MAX_N]; // must set - can also use MAX_N last values from above
  i32 n;            // must set
  void build() {
    if (n == 0)
      return;
    build_dfs(0, 0, n - 1);
  }
  void build_dfs(i32 node, i32 x, i32 y) {
    if (x == y) {
      value[node] = input[x];
    } else {
      i32 left = node * 2 + 1;
      i32 right = node * 2 + 2;
      i32 z = (x + y) / 2;
      build_dfs(left, x, z);
      build_dfs(right, z + 1, y);
      auto res = (value[left] > value[right] ? value[left] : value[right]);
      value[node] = res;
    }
  }
  i32 query(i32 r, i32 s) { return query_dfs(0, 0, n - 1, r, s); }
  i32 query_dfs(i32 node, i32 x, i32 y, i32 r, i32 s) {
    if (x > s || y < r)   // node outside query interval
      return INT32_MIN;   // Might not work depending on input
    if (x >= r && y <= s) // node fully inside query interval
      return value[node];
    i32 left = node * 2 + 1;
    i32 right = node * 2 + 2;
    i32 z = (x + y) / 2;
    auto l_ = query_dfs(left, x, z, r, s);
    auto r_ = query_dfs(right, z + 1, y, r, s);
    return (l_ > r_ ? l_ : r_);
  }
  void update(i32 pos, i32 new_value) {
    update_dfs(pos, new_value, 0, 0, n - 1);
  }
  void update_dfs(i32 pos, i32 new_value, i32 node, i32 x, i32 y) {
    if (x > pos || y < pos)
      return;
    if (x == y) {
      value[node] = new_value;
      return;
    }
    i32 left = node * 2 + 1;
    i32 right = node * 2 + 2;
    i32 z = (x + y) / 2;
    update_dfs(pos, new_value, left, x, z);
    update_dfs(pos, new_value, right, z + 1, y);
    auto res = (value[left] > value[right] ? value[left] : value[right]);
    value[node] = res;
  }

} segtree;

std::vector<i32> adj[MAX_N + 1];
i32 heavy_child[MAX_N + 1];
i32 depth[MAX_N + 1], parent[MAX_N + 1], head[MAX_N + 1];
i32 segtree_pos[MAX_N + 1];
struct Edge {
  i32 a;
  i32 b;
  i32 cost;
} edge[MAX_N + 1];

i32 T, N, i_edge, ti_edge, a, b;
char instruction[20];

i32 get_child(Edge e) {
  if (parent[e.a] == e.b)
    return e.a;
  else
    return e.b;
}
i32 compute_heavy(i32 node, i32 d) {
  depth[node] = d;
  i32 size = 1;
  i32 max_child_size = 0;
  for (auto neigh : adj[node]) {
    if (neigh == parent[node])
      continue;
    parent[neigh] = node;
    auto child_size = compute_heavy(neigh, d + 1);
    if (child_size > max_child_size)
      heavy_child[node] = neigh, max_child_size = child_size;
  }
  return size;
};
i32 decompose(i32 node, i32 curr_head, i32 pos) {
  head[node] = curr_head;
  segtree_pos[node] = pos++;
  if (heavy_child[node] != -1) // Assumes nodes start numbered from 0
    pos = decompose(heavy_child[node], curr_head, pos);
  for (auto neigh : adj[node]) {
    if (neigh == parent[node] || neigh == heavy_child[node])
      continue;
    pos = decompose(neigh, neigh, pos);
  }
  return pos;
}

void build() {
  for (i32 i = 0; i <= N; i++) {
    heavy_child[i] = -1;
    adj[i].clear();
  }

  for (i32 i = 1; i <= N - 1; i++) {
    a = edge[i].a, b = edge[i].b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  auto root = edge[1].a; // random node
  compute_heavy(root, 0);
  decompose(root, root, -1); // root has pos -1
  for (i32 i = 1; i <= N - 1; i++) {
    auto pos = segtree_pos[get_child(edge[i])];
    segtree.input[pos] = edge[i].cost;
  }
  segtree.n = N - 1;
  segtree.build();
}

void update(i32 i_edge, i32 value) {
  auto pos = segtree_pos[get_child(edge[i_edge])];
  segtree.update(pos, value);
}

void swap(i32 &a, i32 &b) {
  i32 temp = a;
  a = b;
  b = temp;
}
i32 query(i32 a, i32 b) {
  i32 max_value = INT32_MIN;
  while (head[a] != head[b]) {
    if (depth[head[a]] > depth[head[b]])
      swap(a, b);
    auto temp = segtree.query(segtree_pos[head[b]], segtree_pos[b]);
    if (temp > max_value)
      max_value = temp;
    b = parent[head[b]];
  }
  if (depth[a] > depth[b])
    swap(a, b);
  auto temp = segtree.query(segtree_pos[a] + 1, segtree_pos[b]);
  if (temp > max_value)
    max_value = temp;
  return max_value;
}

int main() {
  scanf("%ld", &T);

  while (T--) {
    scanf("%ld", &N);
    for (i32 i = 1; i < N; i++) {
      scanf("%ld %ld %ld", &edge[i].a, &edge[i].b, &edge[i].cost);
    }
    build();
    scanf("%s", instruction);
    while (strcmp(instruction, "DONE") != 0) {
      if (strcmp(instruction, "CHANGE") == 0) {
        scanf("%ld %ld", &i_edge, &ti_edge);
        update(i_edge, ti_edge);
      } else {
        scanf("%ld %ld", &a, &b);
        printf("%ld\n", query(a, b));
      }
      scanf("%s", instruction);
    }
  }

  return 0;
}
