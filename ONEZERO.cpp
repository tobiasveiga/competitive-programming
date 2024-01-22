/*
ONEZERO - Ones and zeros
https://www.spoj.com/problems/ONEZERO/

Explanation:
- Brute force
- Start at number '1' and increment as a binary number
- At each increment tests if the number can be divided by n
- If it can be divided then that is the answer and the search can stop

Notes:
- BFS is complicated for large numbers, the queue would need 2 ** 64 values to
store all the 64 digit numbers. Which is too much memory for this problem.
- In practice this solution is similar to a BFS search, but with O(d) memory
instead, d being the number of digits.

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
#define i64 long long

i32 K, n;
char ans[100];

void increment() {
  int i = 0;
  for (; ans[i] != 0; i++) {
    if (ans[i] == '0') {
      ans[i] = '1';
      return;
    } else {
      ans[i] = '0';
    }
  }
  ans[i] = '1';
}

bool divide() {
  auto len = strlen(ans);
  i32 remainder = 0;
  for (int i = len - 1; i >= 0; i--) {
    i32 curr = (ans[i] - '0') + remainder * 10;
    remainder = curr % n;
  }
  return remainder == 0;
}

void solve() {
  memset(ans, 0, 100);
  ans[0] = '1';
  while (!divide())
    increment();
}

int main() {
  std::cin >> K;
  while (K--) {
    std::cin >> n;
    solve();
    for (int i = strlen(ans) - 1; i >= 0; i--)
      printf("%c", ans[i]);
    printf("\n");
  }
}