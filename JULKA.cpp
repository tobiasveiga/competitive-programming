/*
JULKA - Julka
https://www.spoj.com/problems/JULKA/

Explanation:
- Given the linear system below, applies the corresponding operation directly on
the strings
- To simplify the operations, the strings are reversed in the beginning and once
again before writing them out

Linear system:
>> k + n = total
>> k - delta = n

Solutions:
>> k = (total + delta) / 2
>> n = k - delta

ACCEPTED
*/
#include <stdio.h>
#include <string.h>

char total[102], delta[102], klaudia[102], natalia[102];

void reverse(char *a) {
  auto n = strlen(a);
  for (int i = 0; i < n / 2; i++) {
    auto temp = a[i];
    a[i] = a[n - i - 1];
    a[n - i - 1] = temp;
  }
}

void add(char *a, char *b, char *out) {
  char remainder = 0;
  auto n = strlen(a);
  auto m = strlen(b);
  for (int i = 0, j = 0; i < n; i++, j++) {
    auto num1 = (i < n ? a[i] - '0' : 0);
    auto num2 = (i < m ? b[i] - '0' : 0);
    auto curr = num1 + num2 + remainder;
    out[i] = (curr % 10) + '0';
    remainder = curr / 10;
  }
  int i = n;
  if (remainder > 0)
    out[i++] = remainder + '0';
  out[i] = 0;
}
void div2(char *a, char *out) {
  auto remainder = 0;
  auto n = strlen(a);
  for (int i = n - 1; i >= 0; i--) {
    auto curr = a[i] - '0' + remainder;
    out[i] = curr / 2 + '0';
    remainder = 10 * (curr % 2);
  }
  if (out[n - 1] == '0')
    out[n - 1] = 0;
}
void sub(char *a, char *b, char *out) {
  char debt = 0;
  char inc = 0;
  auto n = strlen(a);
  auto m = strlen(b);
  for (int i = 0; i < n; i++) {
    auto num1 = (i < n ? a[i] - '0' : 0);
    auto num2 = (i < m ? b[i] - '0' : 0);
    num1 -= debt;
    inc = (num2 > num1 ? 10 : 0);
    auto curr = num1 - num2 + inc;
    out[i] = (curr % 10) + '0';
    out[i + 1] = 0;
    debt = (num2 > num1 ? 1 : 0);
  }
  for (int i = n - 1; i > 0 && out[i] == '0'; i--)
    out[i] = 0;
}

void solve() {
  reverse(total);
  reverse(delta);
  add(total, delta, klaudia);
  div2(klaudia, klaudia);
  sub(klaudia, delta, natalia);
  reverse(klaudia);
  reverse(natalia);
}

int main() {
  while (scanf("%s %s", total, delta) != EOF) {
    solve();
    printf("%s\n", klaudia);
    printf("%s\n", natalia);
  }
  return 0;
}