/*
HIGHWAYS - Highways
https://www.spoj.com/problems/HIGHWAYS/

Explanation:
- Simple dijkstra solution
- Uses a ordered set as priority queue
- Set compares first the cost, then node id is tie break

Complexity
- Given the graph (V, E)
- For each visited edge in E, if there is a cost improvement, then a value in
the priority queue is updated
- The priority queue update of the cost to a vertex in V takes log(|V|)
- hence O(|E| * log(|V|))

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
using namespace std;

const i32 N = 100'001;
int t;
i32 n, m, source, dest, a, b, c;
struct Node {
  i32 id;
  i32 cost;
};
vector<Node> adj[N];

i32 ans;
i32 cost[N];
struct Compare {
  bool operator()(i32 a, i32 b) {
    return (cost[a] == cost[b] ? a < b : cost[a] < cost[b]);
  }
};
set<i32, Compare> pq;
const i32 INF = INT32_MAX;

void solve() {
  fill(cost, cost + (n + 1), INF);
  pq.clear();
  cost[source] = 0;
  pq.insert(source);
  while (!pq.empty()) {
    auto curr = *pq.begin();
    if (curr == dest)
      return;
    pq.erase(pq.begin());
    for (auto n : adj[curr]) {
      auto new_cost = cost[curr] + n.cost;
      auto old_cost = cost[n.id];
      if (new_cost < old_cost) {
        if (old_cost != INF)
          pq.erase(pq.find(n.id));
        cost[n.id] = new_cost;
        pq.insert(n.id);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> t;
  while (t--) {
    cin >> n >> m >> source >> dest;
    for (i32 i = 1; i <= n; i++)
      adj[i].clear();
    for (i32 i = 0; i < m; i++) {
      cin >> a >> b >> c;
      adj[a].push_back({b, c});
      adj[b].push_back({a, c});
    }
    solve();
    if (cost[dest] == INF)
      cout << "NONE\n";
    else
      cout << cost[dest] << "\n";
  }
  return 0;
}