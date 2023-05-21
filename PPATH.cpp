/**
PPATH - Prime Path
https://www.spoj.com/problems/PPATH/

Solution:
- Precompute primes from 1000 to 9999 using Sieve of Eratosthenes
- Use BFS to get minimum cost
- Speed up BFS by precomputing all prime numbers groups with 3 digits in
common, i.e. 1033 belong to the groups *033, 1*33, 10*3 and 103*

ACCEPTED
**/
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#define i32 long
#include <unordered_map>
#include <unordered_set>

i32 T, cost;
std::string source, dest;
bool isPrime[10'000];
std::unordered_map<std::string, std::vector<std::string>> edges;
std::unordered_set<std::string> visited;
std::string queue[10'000];
bool impossible;

void computeIsPrime() {
  const i32 N = 10'000;
  for (i32 i = 0; i < N; i++)
    isPrime[i] = true;
  for (i32 i = 2; i < sqrt(N); i++)
    if (isPrime[i])
      for (i32 j = pow(i, 2); j < N; j += i)
        isPrime[j] = false;
}
void computeEdges() {
  const i32 N = 10'000;
  for (i32 i = 1000; i < N; i++) {
    if (isPrime[i]) {
      std::string i_string = std::to_string(i);
      for (i32 j = 0; j < 4; j++) {
        std::string key = i_string;
        key[j] = '*';
        if (edges.find(key) != edges.end())
          edges[key].push_back(i_string);
        else
          edges[key] = {i_string};
      }
    }
  }
}

void bfs(std::string root) {
  i32 front = 0;
  i32 rear = 0;
  const char depthBP[] = "****"; // depth break point
  queue[rear++] = root;
  queue[rear++] = depthBP;
  visited.insert(root);
  while (front != rear - 1) {
    const auto curr = queue[front++];
    if (curr == depthBP) {
      queue[rear++] = depthBP;
      cost++;
    }
    if (curr == dest)
      return;
    for (i32 i = 0; i < 4; i++) {
      auto key = curr;
      key[i] = '*';
      if (edges.find(key) != edges.end()) {
        for (const auto &neighbor : edges[key]) {
          if (visited.find(neighbor) == visited.end()) {
            queue[rear++] = neighbor;
            visited.insert(neighbor);
          }
        }
      }
    }
  }
  impossible = true;
  return;
}

void solve() {
  impossible = false;
  cost = 0;
  visited.clear();
  bfs(source);
}

int main() {
  std::cin >> T;
  computeIsPrime();
  computeEdges();
  while (T--) {
    std::cin >> source >> dest;
    solve();
    if (impossible)
      std::cout << "Impossible\n";
    else
      std::cout << cost << "\n";
  }
}