/*
AKBAR - Akbar , The great
https://www.spoj.com/problems/AKBAR/

Explanation:
- Multiple BFS solution starting from each guard
- Each BFS associated with a guard
- Everytime a node is visited with a guard protection, the node is marked with
the guard id (city)
- The BFS loop stops when the BFS depth is too high, meaning the strength of the
rooted guard is not enough. When depth increases, the strength (g) decreases
by 1.
- If a node visited by other guard is found then the solution is not optimal,
since two guards protect the same city
- In the end the total number of visited cities by all guards BFS must be equal
the number of total cities. Otherwise not all cities are protected.

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

int T;
i32 N, R, M, A, B, K, S;

std::vector<int> adj[1'000'000 + 1];
std::vector<int> guards;
i32 strength[1'000'000 + 1];
i32 visited[1'000'000 + 1];
i32 queue[2'000'000 + 2];
i32 root;
i32 total;
bool ans;

bool bfs(i32 city, i32 g) {
  if (visited[city])
    return false;
  i32 front = 0;
  i32 back = 0;
  queue[front++] = city;
  queue[front++] = -1;
  visited[city] = root;
  total++;
  while (back != front) {
    auto curr = queue[back++];
    if (curr == -1) {
      if (back == front)
        break;
      g--;
      queue[front++] = -1;
      continue;
    }
    if (g == 0)
      continue;
    for (auto n : adj[curr]) {
      if (visited[n] == root)
        continue;
      if (visited[n] != 0)
        return false;
      queue[front++] = n;
      visited[n] = root;
      total++;
    }
  }
  return true;
}
void solve() {
  ans = true;
  total = 0;
  for (auto guard : guards) {
    root = guard;
    if (!bfs(guard, strength[guard])) {
      ans = false;
      break;
    }
  }
  if (total != N)
    ans = false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> T;
  while (T--) {
    std::cin >> N >> R >> M;
    for (i32 i = 1; i <= N; i++) {
      adj[i].clear();
    }
    for (i32 i = 0; i < R; i++) {
      std::cin >> A >> B;
      adj[A].push_back(B);
      adj[B].push_back(A);
      visited[A] = 0;
      visited[B] = 0;
    }
    guards.clear();
    for (i32 i = 0; i < M; i++) {
      std::cin >> K >> S;
      strength[K] = S;
      guards.push_back(K);
    }
    solve();
    std::cout << (ans ? "Yes\n" : "No\n");
  }
  return 0;
}