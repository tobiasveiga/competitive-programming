/*
CAPCITY - Capital City
https://www.spoj.com/problems/CAPCITY/

- Kosaraju's algorithm
- Assumes there is only one destination SCC from all other SCCs
- Returns the nodes of the destination SCC sorted


ACCEPTED
*/
#include <algorithm>
#include <stdio.h>
#include <vector>
#define i32 long

const i32 Nmax = 100'001, Mmax = 200'001;
i32 N, M, A, B;
std::vector<i32> adj[Mmax], adj_trans[Mmax];
bool visited1[Nmax], visited2[Nmax];
std::vector<i32> ans;
std::vector<i32> l;
i32 scc[Nmax];

void dfs1(i32 node) {
  visited1[node] = true;
  for (auto neigh : adj[node]) {
    if (!visited1[neigh])
      dfs1(neigh);
  }
  l.push_back(node);
}

void dfs2(i32 node, i32 root) {
  visited2[node] = true;
  scc[node] = root;
  for (auto neigh : adj_trans[node]) {
    if (!visited2[neigh])
      dfs2(neigh, root);
  }
}

int main() {
  scanf("%ld %ld", &N, &M);
  for (i32 i = 0; i < M; i++)
    scanf("%ld %ld", &A, &B), adj[A].push_back(B), adj_trans[B].push_back(A);

  for (i32 i = 1; i <= N; i++) {
    if (!visited1[i])
      dfs1(i);
  }

  for (auto it = l.rbegin(); it != l.rend(); it++) {
    auto node = *it;
    if (!visited2[node])
      dfs2(node, node);
  }

  auto last = scc[*l.begin()];
  for (auto node : l)
    if (scc[node] == last)
      ans.push_back(node);
    else
      break;
  std::sort(ans.begin(), ans.end());

  printf("%ld\n", ans.size());
  for (auto i : ans)
    printf("%ld ", i);
  return 0;
}