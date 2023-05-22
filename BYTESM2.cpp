/*
BYTESM2 - Philosophers Stone
https://www.spoj.com/problems/BYTESM2/

Explanation:
- Bottom up solution using DP
- DP rule is
memo[i][j] = stones[i][j] + max(memo[i][j + k] for k = -1, 0, +1)

ACCEPTED
*/
#include <iostream>
#define i32 long
#define i64 long long

i32 T, nrows, ncols, tiles[100][100], memo[100][100], maxStones;

void reset() { maxStones = 0; }

i32 maxFromBelow(i32 i, i32 j) {
  if (nrows == i + 1)
    return 0;
  i32 *below = memo[i + 1];
  i32 max = below[j];
  if (j > 0)
    max = (max > below[j - 1] ? max : below[j - 1]);
  if (j < ncols - 1)
    max = (max > below[j + 1] ? max : below[j + 1]);
  return max;
}
void solve() {
  // Bottom-up
  for (i32 i = nrows - 1; i >= 0; i--)
    for (i32 j = 0; j < ncols; j++)
      memo[i][j] = tiles[i][j] + maxFromBelow(i, j);
  for (i32 j = 0; j < ncols; j++)
    maxStones = (maxStones > memo[0][j] ? maxStones : memo[0][j]);
}
int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> nrows >> ncols;
    for (i32 i = 0; i < nrows; i++)
      for (i32 j = 0; j < ncols; j++)
        std::cin >> tiles[i][j];
    reset();
    solve();
    std::cout << maxStones << "\n";
  }
  return 0;
}