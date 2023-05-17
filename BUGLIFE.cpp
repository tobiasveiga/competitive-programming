/*
BUGLIFE - A Bug’s Life
https://www.spoj.com/problems/BUGLIFE/
ACCEPTED
*/
#include <iostream>
#include <string.h>
#include <unordered_set>
#include <vector>
#define i64 long long
#define i32 long

i32 T, N, I, a, b;
int visited[2'000], gender[2'000];
std::unordered_set<i32> notVisited;
std::vector<i32> neigh[2'000];
bool hasSus;

void reset() {
  memset(visited, 0, N * sizeof(i32));
  memset(gender, 0, N * sizeof(i32));
  for (i32 i = 0; i < N; i++)
    neigh[i].clear();
  for (i32 i = 0; i < N; i++)
    notVisited.insert(i);
  hasSus = false;
}
bool dfs(i32 bug, i32 currGender) {
  if (visited[bug] != 0)
    if (gender[bug] != currGender)
      return true;
    else
      return false;
  visited[bug] = 1;
  notVisited.erase(notVisited.find(bug));
  gender[bug] = currGender;
  for (auto partner : neigh[bug])
    if (dfs(partner, 1 - currGender))
      return true;
  return false;
}

void solve() {
  while (!notVisited.empty()) {
    auto randomBug = *notVisited.begin();
    if (dfs(randomBug, 1)) {
      hasSus = true;
      return;
    }
  }
}

int main() {
  std::cin >> T;
  for (i32 t = 0; t < T; t++) {
    std::cin >> N >> I;
    reset();
    for (i32 i = 0; i < I; i++) {
      std::cin >> a >> b;
      a--;
      b--;
      neigh[a].push_back(b);
      neigh[b].push_back(a);
    }
    solve();
    std::cout << "Scenario #" << t + 1 << ":\n";
    if (hasSus)
      std::cout << "Suspicious bugs found!\n";
    else
      std::cout << "No suspicious bugs found!\n";
  }
}