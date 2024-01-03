/*
UPDATEIT - Update the array !
https://www.spoj.com/problems/UPDATEIT/

Explanation:
- Uses difference array to store the updates (each happens in O(1)).
- Difference array is not efficient for querying, however in this problem all
queries occur once all updates are made, therefore we can "translate" the whole
difference array into the actual new array and make all queries in O(1);
- The translation operation is done in O(n)

Complexity analysis:
- All updates in O(u)
- Translation in O(n)
- All queries in O(q)
- Each test case is solved in O(u + n + q)

ACCEPTED
*/
#include <stdio.h>
#define i32 long
#define i64 long long

i32 t, n, u, l, r, val, q, idx;

struct DiffArray {
  i32 delta[10'001];
  i32 value[10'000];
  void reset() {
    for (i32 i = 0; i < n; i++)
      delta[i] = 0;
  };
  void update() {
    delta[l] += val;
    delta[r + 1] -= val;
  };
  void translate() {
    value[0] = delta[0];
    for (i32 i = 1; i < n; i++)
      value[i] = value[i - 1] + delta[i];
  };
} diffarray;

int main() {

  scanf("%ld", &t);
  while (t--) {
    scanf("%ld %ld", &n, &u);
    diffarray.reset();
    for (i32 i = 0; i < u; i++) {
      scanf("%ld %ld %ld", &l, &r, &val);
      diffarray.update();
    }
    diffarray.translate();
    scanf("%ld", &q);
    for (i32 i = 0; i < q; i++) {
      scanf("%ld", &idx);
      printf("%ld\n", diffarray.value[idx]);
    }
  }
  return 0;
}