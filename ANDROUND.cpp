/*
ANDROUND - AND Rounds
https://www.spoj.com/problems/ANDROUND/

Explanation:
- Sliding window approach
- Store the count of each bit in the windown of size K
- When the window slides, remove or add the correspoding old / new bits
- At each iteration gets the current number from bit count array
- If a bit has a count == K * 2 + 1 then in that window, all neighbour values
are 1, meaning the results is also 1 in that bit, and 0 otherwise

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long
using namespace std;

int T;
i32 N, K, A[20'000];
i32 cnt[32];

i32 get_curr() {
  auto ans = 0;
  auto t = (K >= N / 2 ? N : K * 2 + 1); // (6, 3) and (5, 2) works
  for (i32 i = 0; i < 32; i++)
    ans += (cnt[i] == t ? 1 << i : 0);
  return ans;
}

void solve_highK() {
  for (i32 i = 0; i < N; i++) {
    for (i32 temp = A[i], j = 0; temp > 0 && j < 32; temp >>= 1, j++)
      if ((temp & 1) == 1)
        cnt[j]++;
  }
  for (i32 i = 0; i < N; i++) {
    cout << get_curr() << " ";
  }
  cout << "\n";
}

void solve() {
  // compute first
  for (i32 i = -K; i < K + 1; i++) {
    for (i32 temp = A[(N + i) % N], j = 0; temp > 0 && j < 32; temp >>= 1, j++)
      if ((temp & 1) == 1)
        cnt[j]++;
  }
  cout << get_curr() << " ";
  // compute all others
  for (i32 i = 1; i < N; i++) {
    auto out = A[(i + N - K - 1) % N];
    for (i32 temp = out, j = 0; temp > 0 && j < 32; temp >>= 1, j++)
      if ((temp & 1) == 1)
        cnt[j]--;
    auto in = A[(i + K) % N];
    for (i32 temp = in, j = 0; temp > 0 && j < 32; temp >>= 1, j++)
      if ((temp & 1) == 1)
        cnt[j]++;
    cout << get_curr() << " ";
  }
  cout << "\n";
}

int main() {
  cin >> T;
  while (T--) {
    cin >> N >> K;
    for (i32 i = 0; i < N; i++) {
      cin >> A[i];
    }
    memset(cnt, 0, sizeof(i32) * 32);
    if (K >= N / 2)
      solve_highK();
    else
      solve();
  }

  return 0;
}