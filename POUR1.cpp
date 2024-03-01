/*
POUR1 - Pouring water
https://www.spoj.com/problems/POUR1/

Explanation:
- BFS approach
- We start with {0, 0}
- Solution is {x, c} or {c, y} for any x or y
- Given any state {x, y}, we have the following 6 options
{a, y}, {x, b}, {0, y}, {x, 0},
{min(x+y, a), x+y - min(x+y, a)}, {x+y - min(x+y, b), min(x+y, b)}
- The answer is the BFS depth when solution is reached.
- If there are no more options to visit, then answer is -1;

NOTE:
- This solution gets TLE with arrays instead of unordered set

ACCEPTED
*/
#include <stdio.h>
#include <unordered_set>
#define i32 long

i32 tc, a, b, c;
i32 ans;

const i32 N = 40'001;
std::unordered_set<i32> visited;
struct Pair {
  i32 x;
  i32 y;
} queue[N];
i32 min(i32 a, i32 b) { return (a < b ? a : b); }

void solve() {
  visited.clear();
  i32 front = 0, back = 0;
  queue[back++ % N] = {0, 0};
  visited.insert(0);
  queue[back++ % N] = {-1, -1};
  ans = 0; // num steps
  while (front != back) {
    const auto curr = queue[front++ % N];
    if (curr.x == -1) {
      if (front == back) {
        ans = -1;
        return;
      }
      queue[back++ % N] = {-1, -1};
      ans++;
      continue;
    }
    if (curr.x == c || curr.y == c)
      return;
    const auto total = curr.x + curr.y;
    const Pair options[] = {
        {a, curr.y},
        {curr.x, b},
        {0, curr.y},
        {curr.x, 0},
        {min(total, a), total - min(total, a)},
        {total - min(total, b), min(total, b)},
    };
    for (const auto op : options) {
      if (visited.find(op.x * N + op.y) == visited.end()) {
        queue[back++ % N] = op;
        visited.insert(op.x * N + op.y);
      }
    }
  }
}
int main() {
  scanf("%ld", &tc);
  while (scanf("%ld %ld %ld", &a, &b, &c) != EOF) {
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}