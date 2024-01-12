/*
ABCPATH - ABC Path
https://www.spoj.com/problems/ABCPATH/

Explanation:
- BFS solution
- From each grid position with a 'A' char, start BFS to measure length of all
paths starting from the respective 'A'

Time complexity
- Each grid position is visited once only by any of the BFS calls
- Hence, O(H * W)

ACCEPTED
*/
#include <stdio.h>

const int N = 50;
int T, H, W, ans;
char grid[N][N + 1];
bool visited[N][N];
struct Pos {
  int h;
  int w;
};

const int M = N * N;
struct Queue {
  Pos arr[M]; // max is probably something close to N * 4;
  int front = 0, back = 0;
  void clear() { front = 0, back = 0; }
  void add(Pos pos) { arr[back++ % M] = pos; }
  Pos pop() { return arr[front++ % M]; }
  bool empty() { return front == back; }
} queue;

void measure(int a, int b) {
  // bfs search
  queue.clear();
  queue.add({a, b});
  visited[a][b] = true;
  queue.add({-1, -1}); // bfs depth sentinel node
  int depth = 1;       // length of path actually
  while (!queue.empty()) {
    auto pos = queue.pop();
    auto a = pos.h, b = pos.w;

    if (a == -1) { // depth increase
      depth++;
      if (!queue.empty())
        queue.add({-1, -1});
      continue;
    }

    ans = (depth > ans ? depth : ans);

    // find valid neighbor paths
    for (int i = a - 1; i < a + 2; i++)
      for (int j = b - 1; j < b + 2; j++) {
        if (i < 0 || i >= H || j < 0 || j >= W)
          continue;
        if (i == a && j == b)
          continue;
        if (visited[i][j])
          continue;
        if (grid[i][j] > 'Z')
          continue;
        if (grid[a][b] + 1 == grid[i][j]) {
          queue.add({i, j});
          visited[i][j] = true;
        }
      }
  }
}
void solve() {
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      if (grid[i][j] == 'A' && !visited[i][j])
        measure(i, j);
}

void reset() {
  ans = 0;
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      visited[i][j] = false;
}

int main() {
  while (true) {
    scanf("%d %d", &H, &W);
    if (H == 0)
      break;
    for (int i = 0; i < H; i++)
      scanf("%s", grid[i]);
    reset();
    solve();
    printf("Case %d: %d\n", ++T, ans);
  }
}