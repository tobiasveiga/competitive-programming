/*
LCA - Lowest Common Ancestor
https://www.spoj.com/problems/LCA/

Solution:
- Imagine the path from each node to the root as a linked list (LL)
- The problem becomes finding the first common node of two LLs
- This can be done by first taking out the difference, d, in length of the two
LLs, which means taking the lengthiest LL and moving up d nodes towards the root
- Then it is just a matter of checking if the current nodes of each LL is the
same, if it is not, move both LLs to the next node, and repeat.
- This solution uses Memoization to compute the height of each node at query
time

ACCEPTED
*/
#include <algorithm>
#include <iostream>
#define i32 long
#define i64 long long

i32 T, N, M, child, Q, v, w;

i32 parent[1'001];
i32 height[1'001];

void initialize() {
  for (i32 i = 0; i < N; i++) {
    parent[i + 1] = -1;
    height[i + 1] = -1;
  }
}

i32 memo_height(i32 node) {
  if (height[node] != -1)
    return height[node];
  else if (parent[node] == -1)
    return 0;
  else {
    height[node] = memo_height(parent[node]) + 1;
    return height[node];
  }
}
void query() {
  auto a = v;
  auto b = w;
  auto h_a = memo_height(a);
  auto h_b = memo_height(b);
  if (h_a < h_b) {
    i32 aux[] = {a, h_a};
    a = b;
    h_a = h_b;
    b = aux[0];
    h_b = aux[1];
  }
  auto diff = h_a - h_b;
  for (i32 i = 0; i < diff; i++)
    a = parent[a];
  for (i32 i = 0; i < h_b; i++) {
    if (a == b) // this won't test if height = 0, since is not necessary
      break;
    a = parent[a];
    b = parent[b];
  }
  std::cout << a << "\n";
}

int main() {

  std::cin >> T;
  for (i32 t = 0; t < T; t++) {
    std::cin >> N;
    initialize();
    for (i32 i = 0; i < N; i++) {
      std::cin >> M;
      for (i32 j = 0; j < M; j++) {
        std::cin >> child;
        parent[child] = i + 1;
      }
    }
    std::cout << "Case " << t + 1 << ":\n";
    std::cin >> Q;
    for (i32 q = 0; q < Q; q++) {
      std::cin >> v >> w;
      query();
    }
  }
}
