/*
QTREE2 - Query on a tree II
https://www.spoj.com/problems/QTREE2/

Explanation:
- Uses binary lifting to quickly move in the tree
- For the DIST intruction stores the total distance using binary lifting
structure
- For the KTH instruction compute the total path node count, then if k >
lca_path_idx, use total - k to move up from the other side

ACCEPTED
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#define i32 long

i32 t, N, a, b, c, k;
char inst[5];

struct Edge {
  i32 to;
  i32 cost;
};
std::vector<Edge> adj[10'001];
i32 ancestor[10'001][14];
i32 dist[10'001][14];
i32 depth[10'001];

void reset() {
  for (i32 i = 1; i <= N; i++)
    adj[i].clear();
  memset(ancestor, 0, sizeof(ancestor));
}

void dfs(i32 curr, i32 parent, i32 cost, i32 d) {
  depth[curr] = d;
  ancestor[curr][0] = parent;
  dist[curr][0] = cost;
  for (auto n : adj[curr]) {
    if (n.to == parent)
      continue;
    dfs(n.to, curr, n.cost, d + 1);
  }
}
void build() {
  dfs(1, 0, 0, 0);
  for (i32 k = 1; k < 14; k++)
    for (i32 i = 1; i <= N; i++) {
      ancestor[i][k] = ancestor[ancestor[i][k - 1]][k - 1];
      dist[i][k] = dist[ancestor[i][k - 1]][k - 1] + dist[i][k - 1];
    }
}

i32 move(i32 &node, i32 steps) {
  i32 d = 0;
  std::vector<i32> bits;
  for (i32 aux = steps, i = 0; aux > 0; aux >>= 1, i++)
    if (aux & 1l)
      bits.push_back(i);
  for (auto h = bits.rbegin(); h != bits.rend(); h++)
    d += dist[node][*h], node = ancestor[node][*h];
  return d;
}
i32 get_dist() {
  i32 da = 0, db = 0;
  auto delta = depth[a] - depth[b];
  if (delta > 0)
    da += move(a, delta);
  else
    db += move(b, -delta);
  if (a == b) {
    if (delta > 0)
      return da;
    else
      return db;
  }
  while (ancestor[a][0] != ancestor[b][0]) {
    for (i32 i = 0; i < 14; i++) {
      if (ancestor[a][i] == ancestor[b][i]) {
        da += dist[a][i - 1];
        db += dist[b][i - 1];
        a = ancestor[a][i - 1];
        b = ancestor[b][i - 1];
        break;
      }
    }
  }
  da += dist[a][0];
  db += dist[b][0];
  return da + db;
}

i32 get_kth() {
  i32 a1 = a, b1 = b; // keep original
  i32 da = 0, db = 0;
  auto delta = depth[a] - depth[b];
  if (delta > 0)
    move(a, delta), da += delta;
  else
    move(b, -delta), db += -delta;
  if (a == b) {
    if (delta > 0) {
      move(a1, k - 1);
      return a1;
    } else {
      move(b1, -delta + 1 - k);
      return b1;
    }
  }
  while (ancestor[a][0] != ancestor[b][0]) {
    for (i32 i = 1; i < 14; i++) {
      if (ancestor[a][i] == ancestor[b][i]) {
        da += (1 << (i - 1));
        db += (1 << (i - 1));
        a = ancestor[a][i - 1];
        b = ancestor[b][i - 1];
        break;
      }
    }
  }
  da++, db++;
  auto total = da + db + 1;
  if (k <= da + 1) {
    move(a1, k - 1);
    return a1;
  } else {
    move(b1, total - k);
    return b1;
  }
}

int main() {
  scanf("%ld", &t);
  while (scanf("%ld", &N) != EOF) {
    reset();
    for (i32 i = 0; i < N; i++) {
      scanf("%ld %ld %ld", &a, &b, &c);
      adj[a].push_back({b, c});
      adj[b].push_back({a, c});
    }
    build();
    while (scanf("%s", inst) != EOF) {
      if (strcmp(inst, "DONE") == 0)
        break;
      else if (strcmp(inst, "DIST") == 0)
        scanf("%ld %ld", &a, &b), printf("%ld\n", get_dist());
      else
        scanf("%ld %ld %ld", &a, &b, &k), printf("%ld\n", get_kth());
    }
  }
}