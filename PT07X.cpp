/*
PT07X - Vertex Cover
https://www.spoj.com/problems/PT07X/

Greedy approach, alternating nodes, seems to only work for binary trees
For other trees, we need a general function

For each node, we always want the minimum subtrees for its children nodes
However, we can't have the situation where the node is not selected and ANY
direct children is also not selected
Hence, for a selected node, any minimum is accepted; for a not selected node,
all children must be selected.

DP induction function,
f(node, state) :=
f(node, selected) =
  1 + sum(min(f(child, selected), f(child, not_selected)) for all children)
f(node, not_selected) =
  sum(f(child, selected) for all children)

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
#define SELECTED 0
#define NOT_SELECTED 1

i32 N, u, v;
std::vector<i32> adj[100'001];
bool visited[100'001];
i32 ans;
i32 memo[100'001][2];

i32 f(i32 node, i32 state) {
  if (memo[node][state] != -1)
    return memo[node][state];

  visited[node] = true; // active only to avoid child coming back

  i32 temp = (state == SELECTED ? 1 : 0);
  for (auto neigh : adj[node]) {
    if (visited[neigh])
      continue;
    if (state == SELECTED)
      temp += std::min(f(neigh, SELECTED), f(neigh, NOT_SELECTED));
    else
      temp += f(neigh, SELECTED);
  }

  visited[node] = false; // this node will be called again later

  memo[node][state] = temp;
  return temp;
}

void solve() {
  if (N == 1) {
    ans = 1;
    return;
  }
  memset(visited, 0, sizeof(visited));
  memset(memo, -1, sizeof(memo));
  ans = std::min(f(u, SELECTED), f(u, NOT_SELECTED));
}

int main() {
  while (scanf("%ld", &N) != EOF) {
    for (i32 i = 0; i <= N; i++)
      adj[i].clear();
    for (i32 i = 0; i < N - 1; i++)
      scanf("%ld %ld", &u, &v), adj[u].push_back(v), adj[v].push_back(u);
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}