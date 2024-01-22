/*
BUSYMAN - I AM VERY BUSY
https://www.spoj.com/problems/BUSYMAN/

Explanation:
- Sort activities by end time
- Always pick the earliest end time activity that does not overlap with
previously choosen activity
- This always works, since for a given last end time or 0 (first iteration),
picking earliest end time activity provides the maximum possibibilities of other
activities to choose.

ACCEPTED
*/
#include <bits/stdc++.h>
#define i32 long

const i32 NMAX = 100'000;
int T;
i32 N, start[NMAX], end[NMAX];
i32 idx[NMAX];

struct Compare {
  bool operator()(i32 a, i32 b) const { return end[a] < end[b]; }
} cmp;

i32 ans;

void solve() {
  for (i32 i = 0; i < N; i++)
    idx[i] = i;
  std::sort(idx, idx + N, cmp);

  ans = 1;
  auto last = end[idx[0]];
  for (i32 i = 1; i < N; i++) {
    if (start[idx[i]] >= last) { // Check condition
      last = end[idx[i]];
      ans++;
    }
  }
}

int main() {
  std::cin >> T;
  while (T--) {
    std::cin >> N;
    for (i32 i = 0; i < N; i++)
      std::cin >> start[i] >> end[i];
    solve();
    printf("%ld\n", ans);
  }
  return 0;
}