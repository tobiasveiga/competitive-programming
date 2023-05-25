/*
EDIST - Edit distance
https://www.spoj.com/problems/EDIST/

Explanation:
- Use inductive approach with DP to save computations
- The edist is of two strings a and b is a function of the edist of the
substrings of a and b
- Given i and j char index of the strings a and b, comparing a[i] and b[j] gives
a few options (see function distance below)

ACCEPTED
*/
#include <algorithm>
#include <iostream>
#include <string.h>
#define i32 long

i32 T, answer;
char source[2001], dest[2001];
i32 N, M;
i32 memo[2000][2000];

void reset() {
  answer = 0;
  N = strlen(source);
  M = strlen(dest);
  for (i32 i = 0; i < 2000; i++)
    for (i32 j = 0; j < 2000; j++)
      memo[i][j] = -1;
}

i32 distance(i32 i, i32 j) {
  if (i >= N && j >= M)
    return 0;
  if (i >= N)
    return M - j;
  if (j >= M)
    return N - i;
  if (memo[i][j] != -1)
    return memo[i][j];
  if (source[i] == dest[j]) {
    memo[i][j] = distance(i + 1, j + 1);
  } else {
    auto options = {
        distance(i + 1, j + 1), // replace
        distance(i + 1, j),     // remove in source
        distance(i, j + 1),     // insert in source
    };
    memo[i][j] = 1 + std::min(options);
  }
  return memo[i][j];
}

void solve() { answer = distance(0, 0); }

int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> source >> dest;
    reset();
    solve();
    std::cout << answer << "\n";
  }

  return 0;
}