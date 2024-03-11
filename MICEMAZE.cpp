/*
MICEMAZE - Mice and Maze
https://www.spoj.com/problems/MICEMAZE/

Explantion:
- Dijkstra from the exit node.

ACCEPTED
*/
#include <queue>
#include <stdio.h>
#include <vector>
#define i32 long

i32 N, E, T, M, a, b, c;
struct Cell {
  i32 to;
  i32 cost;
};
std::vector<Cell> adj[101];
i32 cost[101];
struct Cmp {
  const int operator()(const i32 u, const i32 v) { return cost[u] > cost[v]; }
};
bool visited[101];
i32 ans;

void solve() {
  for (i32 i = 1; i <= N; i++)
    cost[i] = T + 1;
  std::priority_queue<i32, std::vector<i32>, Cmp> q;
  cost[E] = 0, q.push(E);
  while (!q.empty()) {
    auto u = q.top();
    q.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    if (cost[u] <= T)
      ans++;
    for (auto neigh : adj[u]) {
      auto v = neigh.to, c = neigh.cost;
      if (cost[u] + c < cost[v])
        cost[v] = cost[u] + c, q.push(v);
    }
  }
}

int main() {
  scanf("%ld %ld %ld %ld", &N, &E, &T, &M);
  for (i32 i = 0; i < M; i++)
    scanf("%ld %ld %ld", &a, &b, &c), adj[b].push_back({a, c});
  solve();
  printf("%ld\n", ans);
  return 0;
}