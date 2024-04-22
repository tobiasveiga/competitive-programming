/*
BISHOPS - Bishops
https://www.spoj.com/problems/BISHOPS/

Explanation:
- Assumes optimal value is N * 2 - 2
- i.e. fill the first row with N bishops, then fill last row with N-2 bishops
- Represent big integer as char[] and compute N * 2 - 1 in one loop

ACCEPTED
*/
#include <stdio.h>
#include <string.h>

char numstr[102], ans[102];

void solve() {
  auto n = strlen(numstr);
  if (n == 1 && numstr[0] == '1') {
    ans[0] = '1';
    ans[1] = 0;
    return;
  }
  int co = -2;
  int j = 0;
  for (int i = n - 1; i >= 0; i--) {
    auto curr = (numstr[i] - '0') * 2 + co;
    ans[j++] = ((10 + curr) % 10) + '0';
    co = (curr < 0 ? -1 : curr / 10);
  }
  if (co > 0)
    ans[j++] = co + '0';
  ans[j] = 0;
  // reverse
  for (int i = 0; i < j / 2; i++) {
    auto aux = ans[i];
    ans[i] = ans[j - 1 - i];
    ans[j - 1 - i] = aux;
  }
}
int main() {
  while (scanf("%s", numstr) != EOF) {
    solve();
    printf("%s\n", ans);
  }
  return 0;
}