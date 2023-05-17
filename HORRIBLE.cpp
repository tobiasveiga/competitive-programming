/*
HORRIBLE - Horrible Queries
https://www.spoj.com/problems/HORRIBLE/
ACCEPTED
*/
#include <inttypes.h>
#include <iostream>
#include <string.h>
#include <tuple>
#define i32 int32_t
#define i64 int64_t

i32 N, C, type, p, q, v;
i64 segtree[400'000], lazyprop[400'000];

void build() {
  memset(segtree, 0, N * 4 * sizeof(i64));
  memset(lazyprop, 0, N * 4 * sizeof(i64));
};

struct Node {
  i32 id;
  i32 low;
  i32 high;
};
Node genNode(const i32 id, const i32 low, const i32 high) {
  Node node;
  node.id = id;
  node.low = low;
  node.high = high;
  return node;
}
std::tuple<Node, Node> getChildren(const Node node) {
  const auto middle = (node.low + node.high) / 2;
  const Node left = genNode(node.id * 2 + 1, node.low, middle);
  const Node right = genNode(node.id * 2 + 2, middle + 1, node.high);
  return {left, right};
}

void add(const Node node) {
  if (p > node.high || q < node.low)
    return;
  if (p <= node.low && q >= node.high) {
    lazyprop[node.id] += v;
    return;
  }
  const i64 queryInNode = std::min(node.high, q) - std::max(node.low, p) + 1;
  segtree[node.id] += v * queryInNode;
  Node left, right;
  std::tie(left, right) = getChildren(node);
  add(left);
  add(right);
}
void update() { add(genNode(0, 0, N - 1)); }

void propagateUpdate(const Node node) {
  const auto id = node.id;
  const auto nodeSize = node.high - node.low + 1;
  const auto val = lazyprop[id];
  lazyprop[id * 2 + 1] += val;
  lazyprop[id * 2 + 2] += val;
  lazyprop[id] = 0;
  segtree[id] += (val * nodeSize);
}
i64 get(const Node node) {
  if (p > node.high || q < node.low)
    return 0;
  if (p <= node.low && q >= node.high) {
    const auto nodeSize = node.high - node.low + 1;
    return segtree[node.id] + lazyprop[node.id] * nodeSize;
  }
  propagateUpdate(node);
  Node left, right;
  std::tie(left, right) = getChildren(node);
  return get(left) + get(right);
}
i64 query() { return get(genNode(0, 0, N - 1)); }

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &N, &C);
    build();
    for (i32 i = 0; i < C; i++) {
      scanf("%d %d %d", &type, &p, &q);
      p--;
      q--;
      if (type == 0) {
        scanf("%d", &v);
        update();
      } else {
        std::cout << query() << std::endl;
      }
    }
  }
}