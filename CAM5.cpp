/*
CAM5 - prayatna PR
https://www.spoj.com/problems/CAM5/

Multi DFS counting the number of root calls

ACCEPTED
*/
#include <stdio.h>
#include <vector>
#define i32 long

i32 t, N, e, a, b;
bool visited[100'000];
std::vector<i32> adj[100'000];

void dfs(i32 node) {
  visited[node] = true;
  for (auto neigh : adj[node])
    if (!visited[neigh])
      dfs(neigh);
}

int main() {
  scanf("%ld", &t);
  while (t--) {
    scanf("%ld %ld", &N, &e);
    for (i32 i = 0; i < N; i++)
      adj[i].clear(), visited[i] = false;
    for (i32 i = 0; i < e; i++)
      scanf("%ld %ld", &a, &b), adj[a].push_back(b), adj[b].push_back(a);
    i32 cnt = 0;
    for (i32 i = 0; i < N; i++)
      if (!visited[i])
        dfs(i), cnt++;
    printf("%ld\n", cnt);
  }
  return 0;
}