/*
NAKANJ - Minimum Knight moves !!!
https://www.spoj.com/problems/NAKANJ/

Explanation:
- BFS for each test case

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

i32 T;
char START[3], DEST[3];

i32 queue[64], front, back;
bool visited[64];
const i32 N = 64;
// Delta Column/Row
i32 DC[] = {1, 1, -1, -1, 2, 2, -2, -2};
i32 DR[] = {2, -2, 2, -2, 1, -1, 1, -1};

i32 bfs(i32 p, i32 p2) {
  memset(visited, 0, sizeof(visited));
  back = 0;
  front = 0;
  queue[back++] = p;
  visited[p] = true;
  queue[back++] = -1;
  i32 dist = 0;

  while (front != back) {
    auto curr = queue[front++ % N];
    if (curr == -1) {
      dist++;
      if (front != back)
        queue[back++ % N] = -1;
      continue;
    }
    if (curr == p2)
      break;
    auto c = curr % 8, r = curr / 8;
    for (int k = 0; k < 8; k++) {
      auto i = DC[k], j = DR[k];
      if (c + i < 8 && c + i >= 0 && r + j < 8 && r + j >= 0) {
        auto q = c + i + 8 * (r + j);
        if (!visited[q]) {
          visited[q] = true;
          queue[back++ % N] = q;
        }
      }
    }
  }
  return dist;
}

int main() {
  scanf("%ld", &T);
  while (scanf("%s %s", START, DEST) != EOF) {
    auto ans = bfs(START[0] - 'a' + 8 * (START[1] - '1'),
                   DEST[0] - 'a' + 8 * (DEST[1] - '1'));
    printf("%ld\n", ans);
  }
}