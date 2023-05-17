/*
GSS1 - Can you answer these queries I
https://www.spoj.com/problems/GSS1/
ACCEPTED
*/
#include <cmath>
#include <iostream>
#include <tuple>
using namespace std;

// 1024 -  2 - 4 - 8 - 16 - 32 - 64
const int maxNodes = 65536 * 2 - 1;
const int minValue = -1'000'000;
struct Node {
  int64_t any;
  int64_t left;
  int64_t right;
  int64_t total;
};
Node getNullNode() {
  Node node;
  node.any = minValue;
  return node;
}
bool getIsNull(Node node) { return node.any == minValue; }
Node tree[maxNodes];
int N, _N, M, x, y;

Node merge(Node childLeft, Node childRight) {
  if (getIsNull(childLeft))
    return childRight;
  if (getIsNull(childRight))
    return childLeft;
  Node parent;
  parent.left = max(childLeft.left, childLeft.total + childRight.left);
  parent.right = max(childRight.right, childRight.total + childLeft.right);
  parent.any = max(
      max(max(parent.left, parent.right), max(childLeft.any, childRight.any)),
      childLeft.right + childRight.left);
  parent.total = childLeft.total + childRight.total;
  return parent;
}

void mergeAndWrite(int left, int right) {
  // left must be odd
  int parent = (left - 1) / 2;
  tree[parent] = merge(tree[left], tree[right]);
  return;
}

void buildTree() {
  for (int i = _N * 2 - 2; i >= 1; i -= 2)
    mergeAndWrite(i - 1, i);
  return;
}

Node query(int x, int y, int low, int high, int node) {
  if (x <= low && y >= high)
    return tree[node];
  if (x > high || y < low)
    return getNullNode();

  int mid = (low + high - 1) /
            2; // if high = _N = 8 -> mid = 4, splits are 1..4 and 5..8
  int leftChild = node * 2 + 1;
  int rightChild = node * 2 + 2;
  return merge(query(x, y, low, mid, leftChild),
               query(x, y, mid + 1, high, rightChild));
}

int main() {
  cin >> N;
  _N = pow(2, ceil(log2(N)));

  int offset = _N - 1; // the number of non leaves
  int temp;
  for (int i = 0; i < _N; i++) {
    if (i < N)
      cin >> temp;
    else
      temp = 0;
    tree[offset + i].any = temp;
    tree[offset + i].left = temp;
    tree[offset + i].right = temp;
    tree[offset + i].total = temp;
  }
  buildTree();
  cin >> M;
  while (M--) {
    cin >> x >> y;
    cout << query(x, y, 1, _N, 0).any << endl;
  }
  return 0;
}