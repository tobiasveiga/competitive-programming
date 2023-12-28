/*
BRCKTS - Brackets
https://www.spoj.com/problems/BRCKTS/


Explanation:
- This problem is a mixture of the solutions from GSS3 and ANARC09A
- Assume values +1 and -1 for ( and ) respectively
- (1) The sum, stability, from the first char from the left to any char to the
right should never be below 0, indicating too many ) at any given point
- (2) The sum, stability, from first to last position should be 0, indicating
there was an equal number of ( and )
- Since we need information for all intervals in [0, i], with i in [0, n-1] and
we also need to update then fast, best choice is to use a Segment Tree
- We need a total value of the interval for the 2nd stability rule
- We need to know the minimum sum of all these intervals - 1st rule
- The minimum of the sums of one interval can be obtained by combining two of
its subintervals
- min_sum = min(left_min_sum, left_total + right_min_sum)

ACCEPTED
*/
#include <stdio.h>

#define i32 long

i32 n, m, k;
char word[30'001];

i32 min(i32 a, i32 b) { return (a < b ? a : b); }

struct Node {
  i32 total;
  i32 left;
};
struct Segtree {
  Node node[120'000];

  void build(i32 curr, i32 x, i32 y) {
    if (x == y) {
      if (word[x] == '(')
        node[curr] = {+1, +1};
      else
        node[curr] = {-1, -1};
      return;
    }

    auto child_left = curr * 2 + 1;
    auto child_right = child_left + 1;
    auto z = (x + y) / 2;
    build(child_left, x, z);
    build(child_right, z + 1, y);
    auto total = node[child_left].total + node[child_right].total;
    auto left = min(node[child_left].left,
                    node[child_left].total + node[child_right].left);
    node[curr] = {total, left};
  };
  void update(i32 curr, i32 x, i32 y, i32 pos) {
    if (x > pos || y < pos)
      return;
    if (x == y) {
      node[curr] = {-node[curr].total, -node[curr].left};
      return;
    }

    auto child_left = curr * 2 + 1;
    auto child_right = child_left + 1;
    auto z = (x + y) / 2;
    update(child_left, x, z, pos);
    update(child_right, z + 1, y, pos);
    auto total = node[child_left].total + node[child_right].total;
    auto left = min(node[child_left].left,
                    node[child_left].total + node[child_right].left);
    node[curr] = {total, left};
  };
} segtree;

void check() {
  auto root = segtree.node[0];
  if (root.left >= 0 && root.total == 0)
    printf("YES\n");
  else
    printf("NO\n");
}
void replace(i32 pos) { segtree.update(0, 0, n - 1, pos); }
int main() {

  for (i32 t = 0; t < 10; t++) {
    if (scanf("%ld", &n) == EOF)
      return 0;
    printf("Test %ld:\n", t + 1);
    scanf("%s", word);
    segtree.build(0, 0, n - 1);
    scanf("%ld", &m);
    for (i32 i_op = 0; i_op < m; i_op++) {
      scanf("%ld", &k);
      if (k == 0)
        check();
      else
        replace(k - 1);
    }
  }
  return 0;
}