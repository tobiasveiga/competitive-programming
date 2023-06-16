/*
BITMAP - Bitmap
https://www.spoj.com/problems/BITMAP/

Explanation:
- Iterate once over each bitmap value to find all 1s
- In each 1, run BFS to compute distance to other points
- If a distance was already calculated update it if the current is smaller
ACCEPTED
*/
#include <iostream>
#include <stdio.h>
#define i32 long

i32 T, n, m, bitmap[182][182], d[182][182];

struct Point {
  i32 i;
  i32 j;
} queue[182 * 182 * 4 + 182 * 4 + 4 + 182 * 2];

void reset() {
  for (i32 i = 0; i < n; i++)
    for (i32 j = 0; j < m; j++)
      d[i][j] = -1; // set as unvisited node
}

void bfs(Point root) {

  i32 front = 0;
  i32 back = 0;
  i32 depth = 0; // distance from root

  queue[back++] = root;
  queue[back++] = {-2, -2};   // no-node
  while (back - 1 != front) { // if back -1 == front, last no-node was reached
    auto neigh = queue[front++];
    if (neigh.i == -2) {
      depth += 1;
      queue[back++] = {-2, -2}; // no-node
      continue;
    }
    if (neigh.i < 0 || neigh.i >= n || neigh.j < 0 || neigh.j >= m)
      continue;
    if (front > 1 && bitmap[neigh.i][neigh.j] == 1)
      continue;
    auto neigh_d = d[neigh.i][neigh.j];
    if (neigh_d == -1 || depth < neigh_d) {
      d[neigh.i][neigh.j] = depth;
      queue[back++] = {neigh.i - 1, neigh.j + 0};
      queue[back++] = {neigh.i + 1, neigh.j + 0};
      queue[back++] = {neigh.i + 0, neigh.j - 1};
      queue[back++] = {neigh.i + 0, neigh.j + 1};
    }
  }
}

void solve() {
  for (i32 i = 0; i < n; i++)
    for (i32 j = 0; j < m; j++)
      if (bitmap[i][j] == 1)
        bfs({i, j});
}

void show_input() {
  std::cout << "\n INPUT \n";
  for (i32 i = 0; i < n; i++) {
    for (i32 j = 0; j < m - 1; j++)
      std::cout << bitmap[i][j] << " ";
    std::cout << bitmap[i][m - 1] << "\n";
  }
  std::cout << "\n";
}
int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> n >> m;
    getchar(); // skip '\n'
    for (i32 i = 0; i < n; i++) {
      for (i32 j = 0; j < m; j++)
        bitmap[i][j] = getchar() - '0';
      getchar(); // skip '\n'
    }
    reset();
    // show_input();
    solve();
    for (i32 i = 0; i < n; i++) {
      for (i32 j = 0; j < m - 1; j++)
        std::cout << d[i][j] << " ";
      std::cout << d[i][m - 1] << "\n";
    }
  }

  return 0;
}