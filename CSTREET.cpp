/*
CSTREET - Cobbled streets
https://www.spoj.com/problems/CSTREET/

Explanation:
- Kruskal's algorithm

ACCEPTED
*/
#include <algorithm>
#include <stdio.h>
#define i32 long
#define u32 unsigned long

u32 tc, p, n, m, a, b, c;
struct Edge {
  u32 u;
  u32 v;
  u32 w;
} edge[300'000];
u32 link[1'001], size[1'001];
u32 ans;

u32 find(u32 curr) {
  while (link[curr] != curr)
    curr = link[curr];
  return curr;
}
void unify(u32 u, u32 v) {
  if (size[u] > size[v])
    std::swap(u, v);
  link[u] = v, size[v] += size[u];
}

int main() {
  scanf("%lu", &tc);
  while (tc--) {
    scanf("%lu %lu %lu", &p, &n, &m);
    for (i32 i = 0; i < m; i++)
      scanf("%lu %lu %lu", &a, &b, &c), edge[i] = {a, b, c};
    std::sort(edge, edge + m, [](Edge &a, Edge &b) { return a.w < b.w; });
    for (i32 i = 0; i <= n; i++)
      link[i] = i, size[i] = 1;
    ans = 0;
    for (i32 i = 0; i < m; i++) {
      auto u_root = find(edge[i].u), v_root = find(edge[i].v);
      if (u_root != v_root)
        unify(u_root, v_root), ans += edge[i].w;
    }
    ans *= p;
    printf("%lu\n", ans);
  }
}
