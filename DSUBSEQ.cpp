/*
DSUBSEQ - Distinct Subsequences
https://www.spoj.com/problems/DSUBSEQ/

Explanation:
- Assume N = strlen(S)
- Assume nxt[] is the array in which nxt[i] is the position of the next char
S[i] in S, and nxt[i] = INF if none apply.
- Idea is that for any sequence cXcY, c being a char, X and Y being subseq, c
not in X, we know that for X = {} we have ccY which will repeat the count for Y,
f(Y) once with cY.
- Induction function, where n := char index in S
    f(N) = 1;
    f(INF) = 0;
    f(n) = 2 * f(n+1) - f(nxt[n] + 1)

- By opening the recursive function you can verify that all further repetitions
(like in cXcYcZ) are taken care off.

ACCEPTED
*/
#include <stdio.h>
#include <string.h>
#define i32 long

i32 T, N;
char S[100'001];

const i32 INF = 100'002;
const i32 M = 1'000'000'007l;
i32 nxt[100'000], dp[100'000], last[30], ans;

i32 f(i32 n) {
  if (n == N)
    return 1;
  if (n >= INF)
    return 0;
  if (dp[n] != -1)
    return dp[n];
  auto temp = ((2 * f(n + 1) - f(nxt[n] + 1)) + M) % M;
  dp[n] = temp;
  return temp;
}

void solve() {
  N = strlen(S);
  for (i32 i = 0; i < 30; i++)
    last[i] = INF;
  for (i32 i = N - 1; i >= 0; i--) {
    nxt[i] = last[S[i] - 'A'];
    last[S[i] - 'A'] = i;
    dp[i] = -1;
  }
  ans = f(0l);
}

int main() {
  scanf("%ld", &T);
  while (T--) {
    scanf("%s", S);
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}