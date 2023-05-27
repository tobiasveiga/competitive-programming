/*
AIBOHP - Aibohphobia
https://www.spoj.com/problems/AIBOHP/

Explanation:
- Inductive formula with DP for efficiency
- Intuitively we are fixing the string from the borders to the center
- Iterate the string moving two pointers i and j
- Pointer move from extremeties towards the center
- If i > j, nothing to do (cost 0)
- Else f(i, j) = f(i+1, j-1) if s[i] == s[j] else 1+min(f(i, j-1), f(i+1, j))

ACCEPTED
*/
#include <algorithm>
#include <iostream>
#include <string.h>
#define i32 long

i32 T, N, ans;
char word[6101];
i32 memo[6100][6100];

void reset() {
  N = strlen(word);
  for (i32 i = 0; i < N; i++)
    for (i32 j = 0; j < N; j++)
      memo[i][j] = -1;
}
i32 f(i32 i, i32 j) {
  if (i > j)
    return 0;
  if (memo[i][j] != -1)
    return memo[i][j];
  if (word[i] == word[j])
    memo[i][j] = f(i + 1, j - 1);
  else
    memo[i][j] = 1 + std::min(f(i + 1, j), f(i, j + -1));
  return memo[i][j];
}
void solve() { ans = f(0, N - 1); }
int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> word;
    reset();
    solve();
    std::cout << ans << "\n";
  }
  return 0;
}