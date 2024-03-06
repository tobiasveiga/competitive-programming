/*
LABYR1 - Labyrinth
https://www.spoj.com/problems/LABYR1/

Explanation:
- Similar to calculating tree diameter
- Ideally one would compute BFS twice, but the enunciate below is very important
    "There is exactly one path between any two free block"
- meaning DFS depth can be used the same as BFS depth

ACCEPTED
*/
#include <stdio.h>

int TC, C, R;
char labyr[1000][1001];
int ans, x_root, y_root;

struct Pair {
  int x;
  int y;
  Pair add(Pair other) { return {x + other.x, y + other.y}; }
  bool equal(Pair other) { return x == other.x && y == other.y; }
} delta[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, root;

bool validate(Pair curr) {
  int x = curr.x, y = curr.y;
  if (x < 0 || y < 0 || x >= R || y >= C || labyr[x][y] == '#')
    return false;
  return true;
}

void dfs(Pair curr, Pair prev, int depth) {
  if (depth > ans)
    root = curr, ans = depth;
  for (auto d : delta) {
    auto next = curr.add(d);
    if (validate(next) && !next.equal(prev))
      dfs(next, curr, depth + 1);
  }
}

void find_root() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      if (labyr[i][j] == '.') {
        root = {i, j};
        return;
      }
}

void solve() {
  ans = 0;
  find_root();
  dfs(root, {-1, -1}, 0);
  dfs(root, {-1, -1}, 0);
}

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &C, &R);
    for (int i = 0; i < R; i++)
      scanf("%s", labyr[i]);
    solve();
    printf("Maximum rope length is %d.\n", ans);
  }
}