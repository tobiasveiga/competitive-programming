/*
SUBMERGE - Submerging Islands
https://www.spoj.com/problems/SUBMERGE/

Explanation:
- Articulation Point problems solved with Tarjan's algorithm

Accepted
*/
#include <stdio.h>
#include <vector>
#define i32 long

i32 N, M, u, v;
const i32 NMAX = 10'001;
std::vector<i32> adj[NMAX];

i32 ans, cnt;
i32 low[NMAX], disc[NMAX], isAP[NMAX];
bool visited[NMAX];

void dfs(i32 curr, i32 parent) {
  visited[curr] = true;
  low[curr] = disc[curr] = cnt++;
  for (auto n : adj[curr]) {
    if (n == parent)
      continue;
    if (visited[n])
      low[curr] = std::min(low[curr], disc[n]);
    else {
      dfs(n, curr);
      low[curr] = std::min(low[curr], low[n]);
      if (low[n] >= disc[curr]) // n subtree is totally after curr
        if (!isAP[curr])
          ans++, isAP[curr] = true;
    }
  }
}
void dfs_root() {
  i32 curr = 1;
  visited[curr] = true;
  low[curr] = disc[curr] = cnt++;
  i32 unvisisted_children = 0;
  for (auto n : adj[curr])
    if (!visited[n])
      unvisisted_children++, dfs(n, curr);
  if (unvisisted_children > 1)
    ans++;
}

int main() {
  while (true) {
    scanf("%ld %ld", &N, &M);
    if (N == 0 && M == 0)
      break;
    for (i32 i = 0; i < N + 1; i++)
      adj[i].clear(), visited[i] = false, isAP[i] = false;
    for (i32 i = 0; i < M; i++)
      scanf("%ld %ld", &u, &v), adj[u].push_back(v), adj[v].push_back(u);
    ans = 0, cnt = 0;
    dfs_root();
    printf("%ld\n", ans);
  }
  return 0;
}