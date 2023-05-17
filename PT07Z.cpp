/*
PT07Z - Longest path in a tree
https://www.spoj.com/problems/PT07Z/
ACCEPTED
*/
#include <inttypes.h>
#include <iostream>
#include <string.h>
#include <vector>
#define i32 int32_t

i32 N, distance, farNode;
bool visited[10'000];
std::vector<i32> edges[10'000];

void reset() {
  memset(visited, false, sizeof(bool) * N);
  distance = 0;
  farNode = -1;
}

void search(i32 node, i32 dist) {
  visited[node] = true;
  if (dist > distance) {
    distance = dist;
    farNode = node;
  }
  for (const auto &neighbour : edges[node])
    if (!visited[neighbour])
      search(neighbour, dist + 1);
}

void findFurthestFrom(i32 node) {
  reset();
  search(node, 0);
}

int main() {
  std::cin >> N;
  // TODO: what if N = 0 or N = 1?
  i32 u, v;
  for (int i = 0; i < N - 1; i++) {
    std::cin >> u;
    std::cin >> v;
    u--;
    v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  findFurthestFrom(u);
  findFurthestFrom(farNode);
  std::cout << distance << std::endl;
}