/*
SHPATH - The Shortest Path
https://www.spoj.com/problems/SHPATH/

Explanation:
- Dijkstra algorithm for each query

ACCEPTED
*/
#include <queue>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

#define i32 long
const int N = 10'000;

int s, n, p, neigh_id, r;
i32 neigh_cost;
char NAME[11], NAME1[11], NAME2[11];

int source, dest;
i32 cost[N + 1];
std::unordered_map<std::string, int> name_id;
struct Edge {
  int to;
  i32 cost;
};
std::vector<Edge> adj[N + 1];

const i32 INF = 2'000'000; // just a high enough number for this problem

void reset_test_case() {
  for (int i = 1; i <= n; i++)
    adj[i].clear();
  name_id.clear();
}

void reset_query() {
  for (int i = 1; i <= n; i++)
    cost[i] = INF;
}
struct Compare {
  bool operator()(int a, int b) const { return cost[a] > cost[b]; }
  // pq is max heap by default
};
void solve() {
  std::priority_queue<int, std::vector<int>, Compare> pq;
  cost[source] = 0;
  pq.push(source);
  while (!pq.empty()) {
    int u = pq.top();
    if (u == dest)
      return;
    pq.pop();
    for (const auto &edge : adj[u]) {
      int v = edge.to;
      i32 c = edge.cost;
      if (cost[u] + c < cost[v]) {
        cost[v] = cost[u] + c;
        pq.push(v);
      }
    }
  }
}

int main() {
  scanf("%d", &s);
  while (s--) {
    scanf("%d", &n);
    reset_test_case();
    for (int i = 1; i <= n; i++) {
      scanf("%s", NAME);
      name_id[NAME] = i;
      scanf("%d", &p);
      for (int j = 0; j < p; j++) {
        scanf("%d %ld", &neigh_id, &neigh_cost);
        adj[i].push_back({neigh_id, neigh_cost});
        // assumes input edge from the other city
      }
    }
    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
      scanf("%s %s", NAME1, NAME2);
      source = name_id[NAME1];
      dest = name_id[NAME2];
      reset_query();
      solve();
      printf("%ld\n", cost[dest]);
    }
  }
  return 0;
}
