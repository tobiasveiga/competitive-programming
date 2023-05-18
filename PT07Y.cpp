/*
PT07Y - Is it a tree
https://www.spoj.com/problems/PT07Y/

- Assumes a tree as a graph with NO CYCLES and having a SINGLE COMPONENT
- Uses DFS to look for cycles
- At each DFS iteration igores previous node to not repeat the same edge
- Check if all nodes were visited, if not then graph has multiple components

ACCEPTED
*/
#include <iostream>
#include <vector>
#define i32 long
#define i64 long long

i32 N, M, u, v;
int visited[10'000];
std::vector<i32> edges[10'000];
bool isTree;

void reset() {
  for (i32 i = 0; i < N; i++) {
    visited[i] = 0;
    edges[i].clear();
  }
}
bool dfs(i32 node, i32 prev) {
  if (visited[node] == 1)
    return true;
  visited[node] = 1;
  for (auto neigh : edges[node]) {
    if (neigh != prev && dfs(neigh, node))
      return true;
  }
  return false;
}
bool getAllVisited() {
  for (i32 i = 0; i < N; i++)
    if (visited[i] == 0)
      return false;
  return true;
}
void solve() {
  i32 randomNode = u;
  bool hasCycle = dfs(randomNode, -1); // -1 means there is no previous node
  bool allVisited = getAllVisited();
  isTree = !hasCycle && allVisited;
}

int main() {
  std::cin >> N >> M;
  reset();
  for (i32 i = 0; i < M; i++) {
    std::cin >> u >> v;
    u--;
    v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  solve();
  if (isTree)
    std::cout << "YES\n";
  else
    std::cout << "NO\n";
}