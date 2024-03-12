/*
ELEVTRBL - Elevator Trouble
https://www.spoj.com/problems/ELEVTRBL/

Explanation:
- BFS

ACCEPTED
*/
#include <queue>
#include <stdio.h>
#define i32 long

i32 F, S, G, U, D;
i32 ans;
bool visited[(i32)1e6 + 1];

void solve() {
  ans = 0; // depth
  for (i32 i = 0; i <= F; i++)
    visited[i] = false;
  std::queue<i32> q;
  q.push(S);
  q.push(-1);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    if (u == -1) {
      if (q.empty()) {
        ans = -1;
        return;
      }
      ans++, q.push(-1);
      continue;
    }
    if (u == G)
      return;
    if (u + U <= F && !visited[u + U])
      q.push(u + U), visited[u + U] = true;
    if (u - D >= 1 && !visited[u - D])
      q.push(u - D), visited[u - D] = true;
  }
}

int main() {
  while (scanf("%ld %ld %ld %ld %ld", &F, &S, &G, &U, &D) != EOF) {
    solve();
    if (ans != -1)
      printf("%ld\n", ans);
    else
      printf("use the stairs\n");
  }
}